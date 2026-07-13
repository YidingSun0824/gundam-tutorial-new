// check_task6_histograms.C
// Inspect TH1 histograms in GUNDAM output ROOT files.
// Run with: root -l -b -q check_task6_histograms.C

#include <TFile.h>
#include <TKey.h>
#include <TH1.h>
#include <TAxis.h>
#include <TDirectory.h>
#include <TString.h>
#include <iostream>
#include <vector>
#include <string>

// ── helpers ──────────────────────────────────────────────────────────────────

bool shouldHighlight(const TString& path, const TString& title) {
  TString lo_path  = path;  lo_path.ToLower();
  TString lo_title = title; lo_title.ToLower();
  return lo_path.Contains("selection2") || lo_path.Contains("sample2")  ||
         lo_path.Contains("topology2")  ||
         lo_title.Contains("selection2")|| lo_title.Contains("sample2") ||
         lo_title.Contains("topology2");
}

void printEdges(TAxis* ax) {
  int n = ax->GetNbins();
  // always print all edges for up to 20 bins; summarise longer lists
  if (n <= 20) {
    std::cout << "      edges  : [";
    for (int i = 1; i <= n + 1; ++i) {
      if (i > 1) std::cout << ", ";
      std::cout << ax->GetBinLowEdge(i);
    }
    std::cout << "]\n";
  } else {
    std::cout << "      edges  : ["
              << ax->GetBinLowEdge(1) << ", "
              << ax->GetBinLowEdge(2) << ", ..., "
              << ax->GetBinLowEdge(n) << ", "
              << ax->GetBinUpEdge(n)
              << "]  (" << n + 1 << " edges)\n";
  }
}

// ── recursive walker ─────────────────────────────────────────────────────────

int gTotal     = 0;
int gHighlighted = 0;

void walkDir(TDirectory* dir, const std::string& path) {
  TIter next(dir->GetListOfKeys());
  TKey* key = nullptr;

  while ((key = (TKey*)next())) {
    TString name      = key->GetName();
    TString classname = key->GetClassName();
    std::string fullpath = path + "/" + name.Data();

    if (classname.BeginsWith("TDirectory")) {
      TDirectory* sub = (TDirectory*)key->ReadObj();
      if (sub) walkDir(sub, fullpath);

    } else if (classname.BeginsWith("TH1")) {
      TH1* h = (TH1*)key->ReadObj();
      if (!h) continue;

      ++gTotal;
      TString title = h->GetTitle();
      bool hi = shouldHighlight(fullpath.c_str(), title);
      if (hi) ++gHighlighted;

      std::string marker = hi ? "[***] " : "      ";
      std::cout << marker << fullpath << "\n";
      std::cout << "      class  : " << classname << "\n";
      std::cout << "      title  : \"" << title << "\"\n";
      std::cout << "      NbinsX : " << h->GetNbinsX() << "\n";
      printEdges(h->GetXaxis());
      std::cout << "\n";
    }
  }
}

// ── per-file entry ────────────────────────────────────────────────────────────

void inspectFile(const char* fpath) {
  std::cout << "\n";
  for (int i = 0; i < 70; ++i) std::cout << '=';
  std::cout << "\n  FILE: " << fpath << "\n";
  for (int i = 0; i < 70; ++i) std::cout << '=';
  std::cout << "\n\n";

  TFile* f = TFile::Open(fpath);
  if (!f || f->IsZombie()) {
    std::cout << "  ERROR: cannot open file.\n";
    return;
  }

  int before = gTotal;
  walkDir(f, "");

  int found = gTotal - before;
  if (found == 0)
    std::cout << "  No TH1 histograms found.\n";
  else
    std::cout << "  -> " << found << " TH1 histogram(s) in this file.\n";

  f->Close();
}

// ── main ─────────────────────────────────────────────────────────────────────

void check_task6_histograms() {
  const char* files[] = {
    "output/fit/gundamFitter_config_Asimov_DryRun.root",
    "output/fit/gundamFitter_config.root",
  };

  for (const char* f : files) inspectFile(f);

  std::cout << "\n";
  for (int i = 0; i < 70; ++i) std::cout << '=';
  std::cout << "\nSummary: " << gTotal << " TH1 histogram(s) total, "
            << gHighlighted << " highlighted (selection2 / sample2 / topology2).\n";
  for (int i = 0; i < 70; ++i) std::cout << '=';
  std::cout << "\n";
}
