# Basic GUNDAM Example

Introductory tutorial. Three progressive steps, each building on the previous one.

All commands are run from the **repository root**.

---

## Files in this package

| File | Purpose |
|---|---|
| `selection_1d.txt` | Local 1D binning definition (pmu, 6 bins) used by steps 02 and 03 |
| `parameters.txt` | Local machine-readable parameter binning (1 bin, all pmu) used by step 03 |

---

## Steps

### Step 01 — Load dataset

```
gundamFitter -c basic_gundam_example/01_load_dataset.yaml
```

Loads the mock dataset and verifies that the event tree can be read.
Applies the dataset-level cut (`selection != -1`).
No sample binning and no parameters are defined.

### Step 02 — Add event selection

```
gundamFitter -c basic_gundam_example/02_load_dataset_selection.yaml
```

Adds one event selection (`selection == 1`) with 1D binning in muon momentum.
The binning is read directly from the local file `selection_1d.txt`.
No parameters are defined.

### Step 03 — Add normalization parameter

```
gundamFitter -c basic_gundam_example/03_load_dataset_selection_normparam.yaml
```

Adds one free normalization parameter generated from the local file `parameters.txt`.
The single bin in `parameters.txt` (all pmu) creates exactly one parameter that
scales the event weights for the selected sample.

---

## Self-containment

This package supplies its own sample binning (`selection_1d.txt`) and parameter
definition (`parameters.txt`) directly.
It does not reference the modular sample or parameter configuration files inside
`super_advanced_gundam_example/`.
The only shared resource is the ROOT dataset file, which lives in
`super_advanced_gundam_example/inputs/datasets/`.
