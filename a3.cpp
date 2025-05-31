#include <vector>
#include <cmath>

#include <matplot/matplot.h>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>

namespace py = pybind11;

PYBIND11_MAKE_OPAQUE(std::vector<double>)

std::vector<double> gen_cos(double frequency, double start, double end, int num_samples)
{
  std::vector<double> result;
  result.reserve(num_samples);

  const double duration = end - start;
  const double dt = duration / num_samples;

  for (int i=0; i<num_samples; i++) {
    result.push_back(cos(start + i*dt*2*M_PI));
  }

  return result;
}

std::vector<double> gen_sin(double frequency, double start, double end, int num_samples)
{
  std::vector<double> result;
  result.reserve(num_samples);

  const double duration = end - start;
  const double dt = duration / num_samples;

  for (int i=0; i<num_samples; i++) {
    result.push_back(sin(start + i*dt*2*M_PI));
  }

  return result;
}

std::vector<double> gen_square(double frequency, double start, double end, int num_samples)
{
  std::vector<double> result;
  result.reserve(num_samples);

  const double duration = end - start;
  const double dt = duration / num_samples;

  for (int i=0; i<num_samples; i++) {
    result.push_back(sin(start + i*dt*2*M_PI)>0?1:-1);
  }

  return result;
}

std::vector<double> gen_sawtooth(double frequency, double start, double end, int num_samples)
{
  std::vector<double> result;
  result.reserve(num_samples);

  const double duration = end - start;
  const double dt = duration / num_samples;

  // Formula: 2(t*f- (1/2 + ))
  // Source: https://en.wikipedia.org/wiki/Sawtooth_wave
  for (int i=0; i<num_samples; i++) {
    const double t = (start + dt * i) * frequency;
    result.push_back(2.0 * (t-std::floor(t)));
  }

  return result;
}


void plot(const std::vector<double>& y)
{
  // Workaround removing annoying warnings
  // Source: https://github.com/alandefreitas/matplotplusplus/issues/432
  auto f = matplot::figure(false);
  f->backend()->run_command("unset warnings");
  f->ioff();
  std::vector<double> x(y.size());
  for (size_t i = 0; i < y.size(); ++i) x[i] = i;

  matplot::plot(x, y);
  matplot::xlabel("Index");
  matplot::ylabel("Value");
  matplot::title("Plot of Vector Values");

  auto [min_it, max_it] = std::minmax_element(y.begin(), y.end());
  double pad = (*max_it - *min_it) * 0.1;
  matplot::ylim({*min_it - pad, *max_it + pad});

  matplot::show();
}

PYBIND11_MODULE(a3, m)
{
    py::bind_vector<std::vector<double>>(m, "VectorDouble");

    // TODO Module Desc
    //m.doc() = "pybind11 example plugin";

    m.def("plot", &plot, "Plot a signal");

    m.def("cos", &gen_cos, "Generate cos signal");
    m.def("sin", &gen_sin, "Generate sin signal");
    m.def("square", &gen_square, "Generate square signal");
    m.def("sawtooth", &gen_sawtooth, "Generate sawtooth signal");
}
