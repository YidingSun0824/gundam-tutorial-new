# Response Function Plotting

ROOT macro for drawing event-by-event systematic response functions stored in the input ROOT file.

From the `build/plotting` folder, run:

```bash
root -l drawResponseFunctions.C
```

By default, the macro reads:

```text
../mydataset.root
```

and draws the first 5 events.

To specify another file or number of events, run inside ROOT:

```cpp
.x plotting/drawResponseFunctions.C("../mydataset.root", 10)
```

The macro creates a multi-page PDF:

```text
response_functions.pdf
```