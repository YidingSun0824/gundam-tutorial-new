# Response Function Plotting

This folder contains ROOT C++ macros for inspecting the response functions stored in the mock input dataset.

## drawResponseFunctions.C

`drawResponseFunctions.C` reads event-by-event systematic response functions from the `events` TTree in:

```text
example/advanced/inputs/datasets/mydataset.root
```

The response functions are stored in the following branches:

- `par1_TGraph`
- `par2_TGraph`
- `par3_TGraph`

From the repository root, run:

```bash
root -l 'plotting/drawResponseFunctions.C("example/advanced/inputs/datasets/mydataset.root",5)'
```

The second argument specifies the number of events to plot. In this example, the macro draws the response functions for the first five events.

The macro creates the multi-page PDF:

```text
response_functions.pdf
```

The response functions for `par1` and `par2` are smooth. The response function for `par3` is intentionally non-smooth so that different interpolation methods can be tested and compared.