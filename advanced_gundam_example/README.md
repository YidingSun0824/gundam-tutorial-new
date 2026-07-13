# Super Advanced GUNDAM Example

Demonstrates the full modular GUNDAM configuration structure, where the fitter
configuration is divided across multiple YAML files organized by concern.
This package is intended for users who want to understand how a larger analysis
is structured and how configuration responsibilities are separated.

All commands are run from the **repository root**.

---

## Configuration structure

```
advanced_gundam_example/
├── config.yaml              Top-level fitter entry point
└── inputs/
    ├── datasets/            Dataset definition (ROOT file path, tree, selection cut, weights)
    ├── samples/             Sample definitions and 2D sample binning tables
    ├── parameters/          Parameter sets: flux (covariance-matrix) and free normalization
    └── plots/               Plot generator configuration
```

`config.yaml` is the single entry point. It references each sub-config by path
so that each concern (dataset loading, sample binning, parameter definitions,
plotting) can be read and modified independently.

---

## Running

```
gundamFitter -c advanced_gundam_example/config.yaml
```

### Building the input dataset

The mock ROOT dataset must be built before running the fitter.
Run the build macro from the repository root, then move the output to the
expected location:

```
root build/buildInputRootFile.C
mv mydataset.root advanced_gundam_example/inputs/datasets/mydataset.root
```

(The build macro writes `mydataset.root` to the current working directory.
Move it to `./advanced_gundam_example/inputs/datasets/` before running the fitter.)
