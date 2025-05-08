# 3 Assignment
## Directions

- [ ] Signal visualization using [matplotplusplus](https://github.com/alandefreitas/matplotplusplus).
- [ ] [DFT](https://en.wikipedia.org/wiki/Discrete_Fourier_transform) &  inverted
- [ ] [1D & 2D Filter](https://docs.scipy.org/doc/scipy/tutorial/signal.html#filtering)
- [ ] Signal generation with specified frequency (sin, cos, square, triangle)
- [ ] Edge detection (using filters)

Original directions can be find [here](https://github.com/marekjg/tp_projekt_3)(in Polish).

## Development

The easiest way to build it,
is to enter development shell throw `nix develop`.
This should install all requited dependencies.

If you don't use **nix**,
you need to ensure that all required dependencies all installed on your system.

Running `make build` will build whole project and link the library to current python shell.

This linking process isn't persistent after exiting the shell.
