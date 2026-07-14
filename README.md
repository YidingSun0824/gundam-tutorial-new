# Input Tutorial for GUNDAM

## Tutorial structure

This tutorial uses a simplified four-module input layout:

```text
inputs/
├── datasets/    # mock ROOT dataset and dataset config
├── parameters/  # flux/free parameter configs and binning tables
├── samples/     # selection/sample definitions and sample binning tables
└── plots/       # plot configuration
```

The master config is `config.yaml` at the repo root.

The old deep structure (`inputs/fitter/likelihood/...`) has been moved to `_archive/` for reference.

## Building the input files

```bash
root build/buildInputRootFile.C
```

The output should look like:

```
Processing build/buildInputRootFile.C...
File writen in ./example/advanced/inputs/datasets/mydataset.root:/
```

## Running GUNDAM

### Running the fitter

```bash
gundamFitter -c config.yaml -t 4
```

---

## Dial types reference

### Common options (all dial types)

| Option | Description |
|---|---|
| `dialType` | One of: `Normalization`, `Spline`, `Graph`, `Surface`, `Tabulated`, `Kriged`, `Formula` |
| `dialSubType` | Variant within a type (e.g. `MonotonicSpline`, `Bilinear`) |
| `isEnabled` | `true` / `false` — skip this dial set without removing it |
| `applyOnDataSets` | List of dataset names; `["*"]` matches all |
| `applyCondition` | Single ROOT formula string; dial only applies when true |
| `applyConditions` | List of ROOT formula strings (all must be true) |
| `minDialResponse` | Hard floor on the computed weight |
| `maxDialResponse` | Hard ceiling on the computed weight |
| `binningFilePath` | Apply dial only within specific bins |
| `useMirrorDial` | Reflect the dial shape across an edge |
| `mirrorLowEdge` | Lower mirror boundary |
| `mirrorHighEdge` | Upper mirror boundary |
| `allowDialExtrapolation` | Extrapolate beyond the defined parameter range |
| `printDialsSummary` | Print dial summary table at startup |
| `definitionRange` | Parameter range over which the dial is defined |
| `mirrorDefinitionRange` | Definition range used for the mirrored side |
| `dialInputList` | Explicit list of dial input objects (alternative to `dialLeafName`) |
| `dialsTreePath` | Path inside a ROOT file to the tree holding dial objects |

### Type-specific options

#### Normalization
| Option | Description |
|---|---|
| `parametersBinningPath` | Optional `.txt` binning file for bin-by-bin normalisation |

#### Spline
| Option | Description |
|---|---|
| `dialLeafName` | Branch name of `TClonesArray<TGraph>` in the event tree |
| `dialsFilePath` | External ROOT file holding spline objects |
| `dialsList` | Explicit list of spline object names inside `dialsFilePath` |
| `dialSubType` | `Uniform` \| `General` \| `Monotonic` \| `Akima` |

#### Graph
| Option | Description |
|---|---|
| `dialLeafName` | Branch name of `TClonesArray<TGraph>` in the event tree |
| `dialsFilePath` | External ROOT file holding graph objects |
| `dialsList` | Explicit list of graph object names inside `dialsFilePath` |

#### Surface
| Option | Description |
|---|---|
| `dialLeafName` | Branch name identifying which surface bin each event falls in |
| `dialsFilePath` | External ROOT file holding the 2-D surface |
| `dialsList` | Explicit list of surface object names |
| `dialSubType` | `Bilinear` \| `Bicubic` |

#### Tabulated
| Option | Description |
|---|---|
| `tableConfig` | Config block pointing to the pre-computed weight table |

#### Kriged
| Option | Description |
|---|---|
| `tableConfig` | Config block pointing to the kriging data source |

#### Formula
| Option | Description |
|---|---|
| *(formula string)* | ROOT `TFormula` expression evaluated per event; set via the `formula` key. Not GPU-accelerated — avoid in large-scale fits. |
