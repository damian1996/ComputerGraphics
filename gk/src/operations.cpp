#include "operations.h"

Operations::Operations() {
}

Operations::~Operations() {
	for (auto const& x : pens)
		delete x.second;
	for (auto const& x : shapes)
		delete x.second;
	for (auto const& x : kernels)
		delete x.second;
	for (auto const& x : windows)
		delete x.second;
	for (auto const& x : images)
		delete x.second;
}

bool Operations::includePixel(const std::string& name, int x, int y) {
	if(!(x>=windows[name]->x1 && x<windows[name]->x2)) return false;
	if(!(y>=windows[name]->y1 && y<windows[name]->y2)) return false;
	return true;
}

void Operations::load(const std::string& path, const std::string& name) {
	images[name] = new Image();
	images[name]->readPNG(path);
	//windows[name] = new ClippingWindow(0, images[name]->width(), 0, images[name]->height(), images[name]);
}

void Operations::save(const std::string& name, const std::string& path) {
	images[name]->writePNG(path);
}

void Operations::create(const std::string& name, int szer, int wys) {
		images[name] = new Image(szer, wys);
		//windows[name] = new ClippingWindow(0, images[name]->width(), 0, images[name]->height(), images[name]);
}

void Operations::put(const std::string& name, int x, int y, float r, float g, float b) {
	//if(includePixel(name, x, y)) {
		RGBColor& tmp = (*images[name])(x,y);
		tmp.r = r;
		tmp.g = g;
		tmp.b = b;
	//}
}

/*
void Operations::put(const std::string& name, int x, int y, std::string& colorspace, float r, float g, float b) {
	//std::cout << conv.r << std::endl;
	if(includePixel(name, x, y)) {
    RGBColor& tmp = (*images[name])(x,y);
    RGBColor conv = RGBColor(r, g, b);
		if(colorspace=="lrgb") { // LRGBtoSRGB
			  conv = conv.gamma(1.0/2.2);
			  conv = conv.clamp();
		}
    else if(colorspace=="xyz") { // XYZtoSRGB
      float xyz[3] = {r, g, b};
      float lin[3] = {0, 0, 0};
      for(int i=0; i<3; i++) {
        for(int j=0; j<3; j++) {
          for(int k=0; k<1; k++) {
            lin[i] += (trR[i][j]*xyz[j]);
          }
        }
      }
			conv = RGBColor(lin[0], lin[1], lin[2]);
			conv = conv.clamp();
			conv = conv.gamma(1/2.2);
    }
		else if(colorspace=="lab") { // LABtoSRGB
			float x = x0*pow((r+16)/116 + g/500, 3);
			float y = y0*pow((r+16)/116, 3);
			float z = z0*pow((r+16)/116 - b/200, 3);
			RGBColor c = RGBColor(x, y, z);
			c.clamp();
			float xyz[3] = {c.r, c.g, c.b};
			float lin[3] = {0, 0, 0};
			for(int i=0; i<3; i++) {
				for(int j=0; j<3; j++) {
					for(int k=0; k<1; k++) {
						lin[i] += (trR[i][j]*xyz[j]);
					}
				}
			}
			conv = RGBColor(lin[0], lin[1], lin[2]);
			conv = conv.clamp();
			conv = conv.gamma(1/2.2);
		}
		tmp.r = conv.r;
		tmp.g = conv.g;
		tmp.b = conv.b;
	}
}
*/

void Operations::get(const std::string& name, int x, int y) {
	RGBColor tmp = (*images[name])(x, y);
	std::cout << "R: " << tmp.r << " G: " << tmp.g << " B: " << tmp.b << "" << std::endl;
}

/*
void Operations::get(const std::string& name, int x, int y, const std::string& colorspace) {
	RGBColor tmp = images[name](x, y);
	if(colorspace=="lrgb") {
		tmp = tmp.gamma(2.2);
		tmp = tmp.clamp();
		//(srgb → lrgb, srgb → xyz)
	}
	else if(colorspace=="xyz") {
		tmp = tmp.gamma(2.2);
		tmp = tmp.clamp();
		float lin[3] = {tmp.r, tmp.g, tmp.b};
		float xyz[3] = {0, 0, 0};
		for(int i=0; i<3; i++) {
			for(int j=0; j<3; j++) {
				for(int k=0; k<1; k++) {
					xyz[i] += (tr[i][j]*lin[j]);
				}
			}
		}
		tmp = RGBColor(xyz[0], xyz[1], xyz[2]);
		tmp = tmp.clamp();
	}
	else if(colorspace=="lab") {
		tmp = tmp.gamma(2.2);
		tmp = tmp.clamp();
		float lin[3] = {tmp.r, tmp.g, tmp.b};
		float xyz[3] = {0, 0, 0};
		for(int i=0; i<3; i++) {
			for(int j=0; j<3; j++) {
				for(int k=0; k<1; k++) {
					xyz[i] += (tr[i][j]*lin[j]);
				}
			}
		}
		tmp = RGBColor(xyz[0], xyz[1], xyz[2]);
		tmp = tmp.clamp();
		float L = 116*cbrt(tmp.r/y0) - 16;
		float a = 500*(cbrt(tmp.r/x0) - cbrt(tmp.g/y0));
		float b = 200*(cbrt(tmp.g/y0) - cbrt(tmp.b/z0));
		tmp = RGBColor(L, a, b);
		tmp = tmp.clamp();
	}
	std::cout << colorspace << " " << tmp.r << " " << tmp.g << " " << tmp.b << std::endl;
}
*/

//void Operations::fill(const std::string& name, std::string& colorspace, float r, float g, float b) {
void Operations::fill(const std::string& name, float r, float g, float b) {
	RGBColor col(r, g, b);
	images[name]->clear(col);
	/*
	for(int i=0; i<images[name]->width(); i++) {
		for(int j=0; j<images[name]->height(); j++) {
			//put(name, i, j, colorspace, r, g, b);
			put(name, i, j, r, g, b);
		}
	}
	*/
}

void Operations::clip(const std::string& name, int x1, int y1, int x2, int y2) {
	windows[name] = new ClippingWindow(x1, x2, y1, y2, images[name]);
}

void Operations::noclip(const std::string& name) {
	windows[name] = new ClippingWindow(0, images[name]->width(), 0, images[name]->height(), images[name]);
}

void Operations::shrink(const std::string& name, int n) {
	int x = images[name]->width()/n, y = images[name]->height()/n;
  Image* img = new Image(x, y);
	//printf("%d %d\n", ima-es[name].width()/n, images[name].height()/n);
	for(int i=0; i<img->width(); i++) {
			for(int j=0; j<img->height(); j++) {
					float tmpR=0, tmpG=0, tmpB=0;
					for(int k=i*n; k<(i+1)*n; k++) {
							for(int l=j*n; l<(j+1)*n; l++) {
									RGBColor tmp = (*images[name])(k, l);
									tmp.gamma(1.0/2.2);
									tmpR += tmp.r;
									tmpG += tmp.g;
									tmpB += tmp.b;
							}
					}
					RGBColor& shrinkImg = (*img)(i, j);
					shrinkImg.r = tmpR/n*n;
					shrinkImg.g = tmpG/n*n;
					shrinkImg.b = tmpB/n*n;
			}
	}
	for(int i=0; i<img->width(); i++) {
		for(int j=0; j<img->height(); i++) {
			//RGBColor& afterGamma = img(i, j);
			//afterGamma.gamma(2.2);
		}
	}
  images[name] = img;
}

// że najpierw przeliczasz srgb → lrgb, liczysz średnią, a potem z powrotem

void Operations::merge(const std::string& name1, const std::string& name2, float w) {
	RGBColor sec;
	int heightDraw2 = images[name2]->height(), widthDraw2 = images[name2]->width();
	for(int i=0; i<images[name1]->width(); i++) {
		for(int j=0; j<images[name1]->height(); j++) {
			RGBColor& first = (*images[name1])(i, j);
			if(i<widthDraw2 && j<heightDraw2) {
				sec = (*images[name2])(i, j);
			}
			first.r = w*first.r + (1-w)*sec.r;
			first.g = w*first.g + (1-w)*sec.g;
			first.b = w*first.b + (1-w)*sec.b;
			first.clamp();
		}
	}
}

void Operations::colorsplit(const std::string& name, const std::string& type) {
	int wid = images[name]->width(), hei = images[name]->height();
	for(int i=1; i<4; i++)
		create(name+std::to_string(i), wid, hei);

	for(int i=0; i<images[name]->width(); i++) {
		for(int j=0; j<images[name]->height(); j++) {
				RGBColor c = (*images[name])(i,j);
				RGBColor& c1 = (*images[name+std::to_string(1)])(i, j);
				c1.r = c1.g = c1.b = c.r;
				RGBColor& c2 = (*images[name+std::to_string(2)])(i, j);
				c2.r = c2.g = c2.b = c.r;
				RGBColor& c3 = (*images[name+std::to_string(3)])(i, j);
				c3.r = c3.g = c3.b = c.b;
		}
	}
}

void Operations::compare(const std::string& name1, const std::string& name2) {
		int n = images[name1]->width(), k = images[name1]->height();
		float sum = 0;
 		for(int i=0; i<n; i++) {
			for(int j=0; j<k; j++) {
				RGBColor img1 = (*images[name1])(i, j);
				RGBColor img2 = (*images[name2])(i, j);
				float val1 = pow(img1.r-img2.r, 2.0);
				float val2 = pow(img1.g-img2.g, 2.0);
				float val3 = pow(img1.b-img2.b, 2.0);
				sum += (val1+val2+val3);
			}
		}
		sum = sum/(3*n*k);
		//printf("MSE %f\n", sum);
		float psnr = 10*log10(1.0/sum);
		//printf("PSNR %f\n", psnr);
}

void Operations::kernel(const std::string& name, Kernel* k) {
	kernels[name] = k;
}

void Operations::gamma(const std::string& out, const std::string& name, float val) {
		int n = images[name]->width(), k = images[name]->height();
		for(int i=0; i<n; i++) {
				for(int j=0; j<k; j++) {
						(*images[out])(i, j) = (*images[name])(i, j).gamma(val);
				}
		}
}

void Operations::convolveimg(std::string& out, const std::string& in, const std::string& k) {
		Image *localImg = images[in];
		RGBColor img;
		int imgWidth = localImg->width(), imgHeight = localImg->height();
		Kernel* localKernel = kernels[k];
		int kerW = localKernel->width(), kerH = localKernel->height();
		create(out, imgWidth, imgHeight);
		for(int x = 0; x<imgWidth; x++){
				for(int y = 0; y<imgHeight; y++) {
						RGBColor outImg;
	 					for(int p=0; p<kerW; p++) {
								for(int q=0; q<kerH; q++) {
										int xp=clamp(x+p-(kerW-1)/2, imgWidth), yq=clamp(y+q-(kerH-1)/2, imgHeight);
										img = (*localImg)(xp, yq);
										float kpq = localKernel->tab[q][p];
										outImg.r += (kpq*img.r);
										outImg.g += (kpq*img.g);
										outImg.b += (kpq*img.b);
								}
						}
						(*images[out])(x, y) = RGBColor(outImg.r, outImg.g, outImg.b);
				}
		}
}

int Operations::clamp(int xp, int size) {
	if(xp<0) return 0;
	else if(xp>=size) return size-1;
	else return xp;
}

bool Operations::clamp2(int xp, int size) {
	if(xp<0) return false;
	else if(xp>=size) return false;
	else return true;
}

void Operations::haar(const std::string& in, const std::string& out) {
	 int imgX = images[in]->width(), imgY = images[in]->height();
	 float const12p2 = (imgX*imgY)/4;
	 Image* outImg = new Image(imgX, imgY);
	 Image* inImg = images[in];
	 haarRec(inImg, outImg, imgX, imgY);

	 images[out] = outImg;
}

void Operations::haarRec(Image* in, Image* out, int x, int y) {
		int newX = x/2, newY = y/2;
		std::vector<float> apb, amb;
		for(int i=0; i<x; i++) {
			// dla kazdego wiersza jednowymiarowa transformata
			for(int j=0; j<newY; j++) {
				RGBColor& col1 = (*in)(i, 2*j);
				RGBColor& col2 = (*in)(i, 2*j+1);
				apb.push_back(col1.r+col2.r);
				apb.push_back(col1.g+col2.g);
				apb.push_back(col1.b+col2.b);
				amb.push_back(col1.r-col2.r);
				amb.push_back(col1.g-col2.g);
				amb.push_back(col1.b-col2.b);
			}
			for(int j=0; j<y; j++) {
				RGBColor& col = (*in)(i, j);
			}
		}
		if(x==0 && y==0) return;
		haarRec(in, out, x/2, y/2);
}


void Operations::circle(const std::string& name, int x, int y, int r) {
	int x0 = x-r, y0 = y-r;
	for(int i=0; i<32; i++) {

	}
}

void Operations::bezier(const std::string& name, int x0, int y0, int x1, int y1, int x2, int y2, int x3, int y3) {
	std::vector< std::pair<float, float> > dc;
	std::pair<float, float> tab[6];
	for(int i=0; i<16; i++) {
		std::cout << (float) i/16 << std::endl;
		tab[0] = std::make_pair(x0+((float) i/16)*(x1-x0), y0+((float) i/16)*(y1-y0));
		tab[1] = std::make_pair(x1+((float) i/16)*(x2-x1), y1+((float) i/16)*(y2-y1));
		tab[2] = std::make_pair(x2+((float) i/16)*(x3-x2), y2+((float) i/16)*(y3-y2));
		tab[3] = std::make_pair(tab[0].first+((float) i/16)*(tab[1].first-tab[0].first), tab[0].second+((float) i/16)*(tab[1].second-tab[0].second));
		tab[4] = std::make_pair(tab[1].first+((float) i/16)*(tab[2].first-tab[1].first), tab[1].second+((float) i/16)*(tab[2].second-tab[1].second));
		tab[5] = std::make_pair(tab[3].first+((float) i/16)*(tab[4].first-tab[3].first), tab[3].second+((float) i/16)*(tab[4].second-tab[3].second));
		std::cout << tab[5].first << " " << tab[5].second << std::endl;
		dc.push_back(tab[5]);
	}
	for(int i=0; i<15; i++) {
		//line(name, dc[i].first, dc[i].second, dc[i+1].first, dc[i+1].second);
	}
}

void Operations::AddSection(const std::string& name, int x0, int y0, int x1, int y1) {
		//shapes[name] = shared_ptr<Shape>(new Section(x0, y0, x1, y1));
		shapes[name] = new Section(x0, y0, x1, y1);
}

void Operations::AddTriangle(const std::string& name, int x0, int y0, int x1, int y1, int x2, int y2) {
		shapes[name] = new Triangle(x0, y0, x1, y1, x2, y2);
}

std::vector<std::complex<float>> Operations::rowsRecursiveFFT1D(zespo input, int N) {
	int Nprim = N/2;
	if(N==1) return input;
	cmpDabl omegaN = std::exp(cmpDabl(0.0, 1.0*(-2*M_PI)/N));
	cmpDabl omega(1.0, 0.0);
	zespo in0, in1;
	in0.resize(Nprim);
	in1.resize(Nprim);

	for(int i=0; i<N; i++) {
		i%2==0 ? in0[i/2] = input[i] : in1[i/2] = input[i];
	}
	in0 = rowsRecursiveFFT1D(in0, Nprim);
	in1 = rowsRecursiveFFT1D(in1, Nprim);
	for(int i=0; i<Nprim; i++) {
		input[i] = in0[i] + omega*in1[i];
		input[i+Nprim] = in0[i] - omega*in1[i];
		omega = omega*omegaN;
	}
	return input;
}

std::vector<std::complex<float>> Operations::rowsRevRecursiveFFT1D(zespo input, int N) {
	int Nprim = N/2;
	if(N==1) return input;
	cmpDabl omegaN = std::exp(cmpDabl(0.0, 1.0*(2*M_PI)/N));
	cmpDabl omega(1.0, 0.0);
	zespo in0, in1;
	in0.resize(N);
	in1.resize(N);

	for(int i=0; i<N; i++) {
		i%2==0 ? in0[i/2] = input[i] : in1[i/2] = input[i];
	}
	in0 = rowsRevRecursiveFFT1D(in0, Nprim);
	in1 = rowsRevRecursiveFFT1D(in1, Nprim);
	for(int i=0; i<Nprim; i++) {
		input[i] = in0[i] + omega*in1[i];
		input[i+Nprim] = in0[i] - omega*in1[i];
		omega = omega*omegaN;
	}
	return input;
}


void Operations::fft(const std::string& in, const std::string& out) {
		int N = (*images[in]).width();
		images[out] = new Image(N, N);

		zespo input[N];
		for(int i=0; i<N; i++) {
				input[i].resize(N);
				for(int j=0; j<N; j++)
						input[i][j] = cmpDabl((*images[in])(i, j).r, 0);
				input[i] = rowsRecursiveFFT1D(input[i], N);
		}
		for(int i=0; i<N; i++) {
				zespo output;
				output.resize(N);
				for(int j=0; j<N; j++)
						output[j] = input[j][i];

				output = rowsRecursiveFFT1D(output, N);
				for(int j=0; j<N; j++) {
						RGBColor& outPixel = (*images[out])(j, i);
						outPixel.r = std::real(output[j])/N;
						outPixel.g = std::imag(output[j])/N;
						outPixel.b = 0.0f/N;
				}
		}
}

void Operations::ifft(const std::string& in, const std::string& out) {
		int N = (*images[in]).width();
		images[out] = new Image(N, N);

		zespo input[N];
		for(int i=0; i<N; i++) {
				input[i].resize(N);
				for(int j=0; j<N; j++)
						input[i][j] = cmpDabl((*images[in])(i, j).r, (*images[in])(i, j).g);
				input[i] = rowsRevRecursiveFFT1D(input[i], N);
		}
		for(int i=0; i<N; i++) {
				zespo output;
				output.resize(N);
				for(int j=0; j<N; j++)
						output[j] = input[j][i];

				output = rowsRevRecursiveFFT1D(output, N);
				for(int j=0; j<N; j++) {
						RGBColor& outPixel = (*images[out])(j, i);
						float val = std::real(output[j])/N;
						outPixel.r = val;
						outPixel.g = val;
						outPixel.b = val;
				}
		}
}

void Operations::line(Image* img, int x0, int y0, int x1, int y1, Pen* pen) {
		int wsp[4] = {x0, y0, x1, y1};
		if(abs(y1-y0) <= abs(x1-x0)) { // X wiodaca osia (-a/b <= 1)
				if(x0<=x1) { // +X
						if(y0 <= y1) { // y++
								drawLine<0, 0, 1>(img, wsp, pen);
						} else { // y--
								drawLine<0, 0, -1>(img, wsp, pen);
						}
				} else { // -X
						if(y0 <= y1) {
								drawLine<0, 1, 1>(img, wsp, pen);
						} else {
								drawLine<0, 1, -1>(img, wsp, pen);
						}
				}
		} else { // Y wiodaca
				if(y0<=y1) { // +Y
						if(x0 <= x1) { // x++
								drawLine<1, 0, 1>(img, wsp, pen);
						} else { // x--
								drawLine<1, 0, -1>(img, wsp, pen);
						}
				} else { // -Y
						if(x0 <= x1) {
								drawLine<1, 1, 1>(img, wsp, pen);
						} else {
								drawLine<1, 1, -1>(img, wsp, pen);
						}
				}
		}
}

// tan (pochodna <= 1 lub nie) -> 0 (wiodacy X), 1 (wiodacy Y)
// lr - idzie w prawo czy w lewo wzgledem osi kierujacej -> +X/+Y -> 0, -X/-Y -> 1
// ud - w gore czy w dol wzgledem osi kierujacej // y++/x++ -> 1, y--/x-- -> -1
template<int tanx, int lr, int ud>
void Operations::drawLine(Image* temp, int* wsp, Pen* pen) {
	RGBColor p = *(pen->col);
	int a, b;
	(*temp)(wsp[0], wsp[1]) = p;


	int tan2 = (tanx==0) ? 1 : 0;
	int lr2 = (lr==0) ? 1 : 0;
	int sign = (lr==1) ? -1 : 1;

	int j = wsp[lr*2 + tan2];
	int k = wsp[lr2*2 + tanx];

	if(tanx) {
		a = -2*abs(wsp[2]-wsp[0]);
		b = 2*abs(wsp[3]-wsp[1]);
	} else {
		a = -2*abs(wsp[3]-wsp[1]);
		b = 2*abs(wsp[2]-wsp[0]);
	}

	int F_M1 = a + (b>>1);

	for(int i = wsp[lr*2+tanx]+1; i < k; i++)
	{
		 if(F_M1 <= 0)
		 {
			 j = j + sign*ud;
			 F_M1 += (a + b);
		 }
		 else
			 F_M1 += a;

		 if(tanx)
			 (*temp)(j, i) = p;
		 else
			 (*temp)(i, j) = p;
	 }
}

void Operations::polygon(const std::string& name, const std::string& pen, int n, const std::vector<std::pair<int, int>>& v) {
	Image* img = images[name];
	Pen* p = pens[pen];
	#pragma omp parallel for
	for(int i=0; i<n-1; i++) {
		line(img, v[i].first, v[i].second, v[i+1].first, v[i+1].second, p);
	}
	line(img, v[n-1].first, v[n-1].second, v[0].first, v[0].second, p);
}

void Operations::addPen(const std::string& name, float r, float g, float b) {
		pens[name] = new Pen(r, g, b);
}

float Operations::noise(int x, int y, int z) {
		// std::hash
}

void Operations::polygonobj(const std::string& name, int n, const std::vector<std::pair<double, double>>& vertices) {
		polygons[name] = new Polygon(n, vertices);
}

void Operations::draw(const std::string& image, const std::string& pen, const std::string& namePolygon) {
		polygons[namePolygon]->draw(images[image], pens[pen]);
}

void Operations::translate(const std::string& name, double x, double y) {
		std::vector<double> mat = {1, 0, x, 0, 1, y, 0, 0, 1};
		matrices[name] = new Matrix(3, 3, mat);
}

void Operations::scale(const std::string& name, double x, double y) {
		std::vector<double> mat = {x, 0, 0, 0, y, 0, 0, 0, 1};
		matrices[name] = new Matrix(3, 3, mat);
}

void Operations::shear(const std::string& name, double x, double y) {
		std::vector<double> mat = {1, x, 0, y, 1, 0, 0, 0, 1};
		matrices[name] = new Matrix(3, 3, mat);
}

void Operations::rotate(const std::string& name, double angle) {
		std::vector<double> mat = {cos(angle), -sin(angle), 0, sin(angle), cos(angle), 0, 0, 0, 1};
		matrices[name] = new Matrix(3, 3, mat);
}

void Operations::transform(const std::string& name1, const std::string& affine, const std::string& name2) {
		polygons[name2] = polygons[name1]->transform(matrices[affine]);
		//polygons[name2] = dynamic_cast<Polygon*>(sh);
}

/*
//NAIVE
void Operations::fft(const std::string& in, const std::string& out) {
	int N = (*images[in]).width();
	images[out] = new Image(N, N);
	float pi = (-2*M_PI)/N;
	for(int k=0; k<N; k++) {
		for(int l=0; l<N; l++) {
			cmpDabl sum(0.0, 0.0);

			for(int x=0; x<N; x++) {
				cmpDabl sumVal(0.0, 0.0);
				for(int y=0; y<N; y++) {
					RGBColor color = (*images[in])(x, y);
					cmpDabl i(0.0,1.0);
					i *= (pi*l*y);
					sumVal += (cmpDabl(color.r, 0.0)*std::exp(i));
				}
				cmpDabl j(0.0,1.0);
				j *= (pi*k*x);
				sum += (sumVal*std::exp(j));
			}
			RGBColor& outPixel = (*images[out])(k, l);
			outPixel.r = std::real(sum)/N;
			outPixel.g = std::imag(sum)/N;
			outPixel.b = 0.0f/N;
		}
	}
}

void Operations::ifft(const std::string& in, const std::string& out) {
	int N = (*images[in]).width();
	images[out] = new Image(N, N);
	float pi = (2*M_PI)/N;

	for(int k=0; k<N; k++) {
		for(int l=0; l<N; l++) {
			cmpDabl sum(0.0, 0.0);

			for(int x=0; x<N; x++) {
				cmpDabl sumVal(0.0, 0.0);
				for(int y=0; y<N; y++) {
					RGBColor color = (*images[in])(x, y);
					cmpDabl i(0.0,1.0);
					i *= (pi*l*y);
					sumVal += (cmpDabl(color.r, color.g)*std::exp(i));
				}
				cmpDabl j(0.0,1.0);
				j *= (pi*k*x);
				sum += (sumVal*std::exp(j));
			}
			RGBColor& outPixel = (*images[out])(k, l);
			float val = std::real(sum)/N;
			outPixel.r = val;
			outPixel.g = val;
			outPixel.b = val;
		}
	}
}
*/
