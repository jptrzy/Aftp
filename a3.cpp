#include <vector>
#include <complex>
#include <cmath>

#include <matplot/matplot.h>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>

namespace py = pybind11;

PYBIND11_MAKE_OPAQUE(std::vector<double>)
PYBIND11_MAKE_OPAQUE(std::vector<std::complex<double>>)

std::vector<double> gen_cos(double freq, double start, double end, int num_samples)
{
  std::vector<double> result;
  result.reserve(num_samples);

  const double duration = end - start;
  const double dt = duration / num_samples;

  for (int i=0; i<num_samples; i++) {
    result.push_back(cos((start + i*dt*2*M_PI)*freq));
  }

  return result;
}

std::vector<double> gen_sin(double freq, double start, double end, int num_samples)
{
  std::vector<double> result;
  result.reserve(num_samples);

  const double duration = end - start;
  const double dt = duration / num_samples;

  for (int i=0; i<num_samples; i++) {
    result.push_back(sin((start + i*dt*2*M_PI)*freq));
  }

  return result;
}

std::vector<double> gen_square(double freq, double start, double end, int num_samples)
{
  std::vector<double> result;
  result.reserve(num_samples);

  const double duration = end - start;
  const double dt = duration / num_samples;

  for (int i=0; i<num_samples; i++) {
    result.push_back(sin((start + i*dt*2*M_PI)*freq)>0?1:-1);
  }

  return result;
}

std::vector<double> gen_sawtooth(double freq, double start, double end, int num_samples)
{
  std::vector<double> result;
  result.reserve(num_samples);

  const double duration = end - start;
  const double dt = duration / num_samples;

  // Formula: 2(t*f- (1/2 + ))
  // Source: https://en.wikipedia.org/wiki/Sawtooth_wave
  for (int i=0; i<num_samples; i++) {
    const double t = (start + dt * i) * freq;
    result.push_back(2.0 * (t-std::floor(t)));
  }

  return result;
}

void plot(const std::vector<double>& x, const std::vector<double>& y)
{
  // Workaround removing annoying warnings
  // Source: https://github.com/alandefreitas/matplotplusplus/issues/432
  auto f = matplot::figure(true);
  f->backend()->output("plot.png");
  f->backend()->run_command("unset warnings");
  f->ioff();

  matplot::plot(x, y);
  matplot::xlabel("Index");
  matplot::ylabel("Value");
  matplot::title("Plot of Vector Values");
  matplot::grid(true);

  auto [min_it, max_it] = std::minmax_element(y.begin(), y.end());
  double pad = (*max_it - *min_it) * 0.1;
  matplot::ylim({*min_it - pad, *max_it + pad});

  f->draw();
}

void plot_simple(const std::vector<double>& y)
{
  std::vector<double> x(y.size());
  for (size_t i = 0; i < y.size(); ++i) x[i] = i;

  plot(x, y);
}

void plot_complex(const std::vector<std::complex<double>>& signal)
{

  // Fixes misleading symmetry
  int N = signal.size() / 2.;

  std::vector<double> x;
  x.reserve(N);
  std::vector<double> y;
  y.reserve(N);

  for (size_t i = 0; i < N; ++i) {
    x.push_back(static_cast<double>(i));      // frequency bin
    y.push_back(std::abs(signal[i]));
  }

  plot(x, y);
}

// Based on past imp
// Source:: https://jptrzy.gitlab.io/complex-numbers-demo
std::vector<std::complex<double>> compute_dft(const std::vector<double>& signal)
{
    int N = static_cast<int>(signal.size());
    std::vector<std::complex<double>> result(N);

    const double pi = std::acos(-1);
    for (int k = 0; k < N; ++k) {
        std::complex<double> sum = 0.0;
        for (int n = 0; n < N; ++n) {
            double angle = -2.0 * pi * k * n / N;
            sum += signal[n] * std::complex<double>(std::cos(angle), std::sin(angle));
        }
        result[k] = sum;
    }

    return result;
}

std::vector<double> compute_idft(const std::vector<std::complex<double>>& freq_data)
{
    int N = static_cast<int>(freq_data.size());
    std::vector<double> signal(N);

    const double pi = std::acos(-1);
    for (int n = 0; n < N; ++n) {
        std::complex<double> sum = 0.0;
        for (int k = 0; k < N; ++k) {
            double angle = 2.0 * pi * k * n / N;
            sum += freq_data[k] * std::complex<double>(std::cos(angle), std::sin(angle));
        }
        signal[n] = sum.real() / N;
    }

    return signal;
}


std::vector<double> apply_filter_1d(std::vector<double> signal, double value)
{
    for (int n = 0; n < signal.size(); ++n) {
      signal[n] *= value;
    }

    return signal;
}

std::vector<std::complex<double>> apply_filter_2d(std::vector<std::complex<double>> signal, double value)
{
    for (int n = 0; n < signal.size(); ++n) {
      signal[n] *= value;
    }

    return signal;
}

std::vector<std::complex<double>> edge_detection(std::vector<std::complex<double>> signal)
{
  // TODO
  return signal;
}


PYBIND11_MODULE(a3, m)
{
    py::bind_vector<std::vector<double>>(m, "VectorDouble");
    py::bind_vector<std::vector<std::complex<double>>>(m, "VectorComplex");

    // TODO Module Desc
    //m.doc() = "pybind11 example plugin";

    m.def("plot", &plot_simple, "Plot a signal");
    m.def("cplot", &plot_complex, "Plot complex signal");

    m.def("cos", &gen_cos, "Generate cos signal");
    m.def("sin", &gen_sin, "Generate sin signal");
    m.def("square", &gen_square, "Generate square signal");
    m.def("sawtooth", &gen_sawtooth, "Generate sawtooth signal");

    m.def("dft", &compute_dft, "Compute dft");
    m.def("idft", &compute_idft, "Compute inverse dft");

    m.def("filter1d", &apply_filter_1d, "Apply 1d filter");
    m.def("filter2d", &apply_filter_2d, "Apply 2d filter");

    m.def("edge", &edge_detection, "Edge Detection");
}
