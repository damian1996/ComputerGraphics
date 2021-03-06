#ifndef WDGK_OPERATIONS_HEADER
#define WDGK_OPERATIONS_HEADER

#include <cmath>
#include <iostream>
#include <complex>
#include <map>
#include <memory>
#include <sstream>
#include <string>
#include <vector>
#include <utility>
#include <string>
#include <functional>

#include "Triangle.h"
#include "Section.h"
#include "Shape.h"
#include "image.h"
#include "clipwindow.h"
#include "kernel.h"
#include "pen.h"
#include "Polygon.h"
#include "Matrix.h"

class Operations {
public:
  float x0 = 94.81;
  float y0 = 100.0;
  float z0 = 107.3;
  float trR[3][3] = {
    {3.2410, -1.5374, -0.4986},
    {-0.9692, 1.8760, 0.0416},
    {0.0556, -0.2040, 1.0570}
  };
  float tr[3][3] = {
    {0.4124, 0.3576, 0.1805},
    {0.2126, 0.7152, 0.0722},
    {0.0193, 0.1192, 0.9505}
  };
  std::map<std::string, Image*> images;
  std::map<std::string, ClippingWindow*> windows;
  std::map<std::string, Kernel*> kernels;
  std::map<std::string, Pen*> pens;
  std::map<std::string, Shape*> shapes;
  std::map<std::string, Polygon*> polygons;
  std::map<std::string, Matrix*> matrices;
  typedef std::vector<std::complex<float>> zespo;
  typedef std::complex<float> cmpDabl;
	Operations();
  ~Operations();
  bool includePixel(const std::string& name, int x, int y);
  void load(const std::string& path, const std::string& name);
  void save(const std::string& name, const std::string& path);
  void create(const std::string& name, int wid, int hei);
  void put(const std::string& name, int x, int y, float r, float g, float b);
  //void put(const std::string& name, int x, int y, std::string& colorspace, float r, float g, float b);
  void get(const std::string& name, int x, int y);
  //void get(const std::string& name, int x, int y, const std::string& colorspace);
  //void fill(const std::string& name, std::string& colorspace, float r, float g, float b);
  void fill(const std::string& name, float r, float g, float b);
  void clip(const std::string& name, int x1, int y1, int x2, int y2);
  void noclip(const std::string& name);
  void shrink(const std::string& name, int n);
  void merge(const std::string& name1, const std::string& name2, float weight);
  void colorsplit(const std::string& name, const std::string& type);
  void compare(const std::string& name1, const std::string& name2);
  void kernel(const std::string& name, Kernel *k);
  void gamma(const std::string& out, const std::string& name, float val);
  void convolveimg(std::string& out, const std::string& in, const std::string& k);
  int clamp(int xp, int size);
  bool clamp2(int xp, int size);
  void haar(const std::string& in, const std::string& out);
  void haarRec(Image* in, Image* out, int x, int y);
  void line(Image* img, int x0, int y0, int x1, int y1, Pen* pen);
  template<int tan, int lr, int ud>
  void drawLine(Image* temp, int* wsp, Pen* pen);
  void circle(const std::string& name, int x, int y, int r);
  void bezier(const std::string& name, int x0, int y0, int x1, int y1, int x2, int y2, int x3, int y3);
  void AddSection(const std::string& name, int x0, int y0, int x1, int y1);
  void AddTriangle(const std::string& name, int x0, int y0, int x1, int y1, int x2, int y2);
  std::vector<std::complex<float>> rowsRecursiveFFT1D(zespo input, int N);
  std::vector<std::complex<float>> rowsRevRecursiveFFT1D(zespo input, int N);
  void fft(const std::string& in, const std::string& out);
  void ifft(const std::string& in, const std::string& out);
  void polygon(const std::string& name, const std::string& pen, int n, const std::vector<std::pair<int, int>>& v);
  void addPen(const std::string& name, float r, float g, float b);
  float noise(int x, int y, int z);
  void polygonobj(const std::string& name, int n, const std::vector<std::pair<double, double>>& v);
  void draw(const std::string& image, const std::string& pen, const std::string& namePolygon);
  void translate(const std::string& name, double x, double y);
  void scale(const std::string& name, double x, double y);
  void shear(const std::string& name, double x, double y);
  void rotate(const std::string& name, double angle);
  void transform(const std::string& name1, const std::string& affine, const std::string& name2);
};

#endif
