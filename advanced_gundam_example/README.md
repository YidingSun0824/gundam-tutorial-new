# Advanced GUNDAM Example

Builds on the Basic tutorial. Demonstrates multiple concurrent selections,
multiple free normalization parameters, spline response dials, and correlated
normalization parameters driven by a covariance matrix.

All commands are run from the **repository root**.

---

## Files in this package

| File | Purpose |
|---|---|
| `selection_1d.txt` | 1D binning in pmu (6 bins) — used by steps 04–07 |
| `selection_2d.txt` | 2D binning in pmu × pp (33 bins) — used by steps 04–07 |
| `selection_3d.txt` | 3D binning in enu × pmu × pp (8 bins) — used by steps 04–07 |
| `parameters.txt` | Free normalization parameter binning (reaction × pmu, 10 bins) — used by steps 05–06 |
| `correlated_parameters.txt` | Parameter binning for the correlated set (enu, 11 bins) — used by step 07 |
| `covarianceFile.root` | Covariance matrix ROOT file for the correlated parameter set — used by step 07 |

---

## Steps

### Step 04 — Multiple selections

```
gundamFitter -c advanced_gundam_example/04_multiple_selections.yaml
```

Defines three concurrent samples, each with a different binning dimensionality:

- Selection 1 uses `selection_1d.txt` (1D: pmu)
- Selection 2 uses `selection_2d.txt` (2D: pmu × pp)
- Selection 3 uses `selection_3d.txt` (3D: enu × pmu × pp)

No parameters are defined.

### Step 05 — Multiple free normalization parameters

```
gundamFitter -c advanced_gundam_example/05_multiple_norm_parameters.yaml
```

Adds 10 free normalization parameters generated from `parameters.txt`.
Each row in `parameters.txt` defines one parameter bin in reaction × pmu space.

### Step 06 — Spline response example

```
gundamFitter -c advanced_gundam_example/06_spline_response_example.yaml
```

Extends step 05 with a Spline dial (`dialType: Spline`, `dialSubType: not-a-knot`)
reading the per-event response function from the `par2_TGraph` branch.
The Spline parameter set is disabled (`isEnabled: false`) until the response
function knots have been validated.

### Step 07 — Correlated normalization parameters

```
gundamFitter -c advanced_gundam_example/07_correlated_norm_parameters.yaml
```

Replaces free normalization parameters with a covariance-matrix-driven set.
The parameter binning is read from `correlated_parameters.txt` (enu, 11 bins)
and the covariance matrix is read from `covarianceFile.root`.

---

## Self-containment

This package supplies its own sample binnings, parameter binnings, and covariance
matrix directly.
It does not reference the modular sample or parameter configuration files inside
`super_advanced_gundam_example/`.
The only shared resource is the ROOT dataset file, which lives in
`super_advanced_gundam_example/inputs/datasets/`.
