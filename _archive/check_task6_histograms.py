#!/usr/bin/env python3
"""
check_task6_histograms.py
Inspect TH1 histograms in GUNDAM output ROOT files.
Highlights histograms related to Selection 2 / topology 2.
"""

import sys
import ROOT

ROOT.gROOT.SetBatch(True)
ROOT.gErrorIgnoreLevel = ROOT.kError  # suppress Info/Warning noise

ROOT_FILES = [
    "output/fit/gundamFitter_config_Asimov_DryRun.root",
    "output/fit/gundamFitter_config.root",
]

HIGHLIGHT_KEYWORDS = {"selection2", "sample2", "topology2", "2"}

RESET  = "\033[0m"
YELLOW = "\033[33m"
CYAN   = "\033[36m"
BOLD   = "\033[1m"


def should_highlight(name: str, title: str) -> bool:
    text = (name + " " + title).lower()
    return any(kw in text for kw in HIGHLIGHT_KEYWORDS)


def format_edges(axis, max_show: int = 8) -> str:
    n = axis.GetNbins()
    edges = [round(axis.GetBinLowEdge(i), 6) for i in range(1, n + 2)]
    if len(edges) <= max_show:
        return str(edges)
    return f"[{edges[0]}, {edges[1]}, ..., {edges[-2]}, {edges[-1]}]  ({len(edges)} edges)"


def walk(directory, path: str, results: list):
    for key in directory.GetListOfKeys():
        name = key.GetName()
        classname = key.GetClassName()
        fullpath = f"{path}/{name}"

        if "TDirectory" in classname or "TFile" in classname:
            subdir = key.ReadObj()
            walk(subdir, fullpath, results)
        elif classname.startswith("TH1") or classname.startswith("TH2"):
            h = key.ReadObj()
            if h:
                results.append((fullpath, classname, h.GetTitle(),
                                 h.GetNbinsX(), h.GetXaxis()))


def inspect_file(fpath: str):
    print(f"\n{'='*70}")
    print(f"  FILE: {fpath}")
    print(f"{'='*70}")

    f = ROOT.TFile.Open(fpath)
    if not f or f.IsZombie():
        print(f"  ERROR: cannot open file.")
        return

    results = []
    walk(f, "", results)

    if not results:
        print("  No TH1/TH2 histograms found.")
        f.Close()
        return

    print(f"  Found {len(results)} histogram(s).\n")

    highlighted = []
    for fullpath, classname, title, nbins, xaxis in results:
        flag = should_highlight(fullpath, title)
        prefix = f"{YELLOW}{BOLD}[*]{RESET} " if flag else "    "
        print(f"{prefix}{CYAN}{fullpath}{RESET}")
        print(f"      class  : {classname}")
        print(f"      title  : {title!r}")
        print(f"      NbinsX : {nbins}")
        print(f"      edges  : {format_edges(xaxis)}")
        print()
        if flag:
            highlighted.append(fullpath)

    if highlighted:
        print(f"{YELLOW}{BOLD}Highlighted (selection2 / topology2 / '2' match):{RESET}")
        for p in highlighted:
            print(f"  {p}")
    else:
        print("  (no histograms matched the highlight keywords)")

    f.Close()


def main():
    for fpath in ROOT_FILES:
        inspect_file(fpath)
    print(f"\n{'='*70}")
    print("Done.")


if __name__ == "__main__":
    main()
