using namespace env;

void drawAll (void) {
	// mapping --------------------------------------
	for (int iy = 0; iy < sizeY; ++iy)
		for (int ix = 0; ix < sizeX; ++ix) {
			tempRect.setPosition(step * iy, step * ix);

			if (status[iy][ix] == indvs + 1) 
				tempRect.setFillColor(sf::Color::Green); // medicine
			else if (status[iy][ix] == indvs + 2) 
				tempRect.setFillColor(sf::Color::Red); // block
			else if (!status[iy][ix]) 
				tempRect.setFillColor(Gray); // void
			else
				tempRect.setFillColor(sf::Color(100 + int(float(pops[status[iy][ix] - 1].state) / topheal * 155), 100 + int(float(pops[status[iy][ix] - 1].state) / topheal * 155), 100 + int(float(pops[status[iy][ix] - 1].state) / topheal * 155))); // person

			window.draw(tempRect);
		}
}

void getChoise (std::vector<double> &temp) {
	temp[0] = temp[0] + temp[1] + temp[2]; 
	temp[1] = temp[3] + temp[4] + temp[5];
	temp[2] = temp[6] + temp[7] + temp[8];
	temp[3] = temp[9] + temp[10] + temp[11];
   
	double buffer = 0;
	for (int it = 0; it < 4; ++it)
		if (temp[it] > buffer) buffer = temp[it];

	for (int it = 0; it < 4; ++it)
		temp[it] /= buffer;
}

double gmax (std::vector<double> in) {
	double maxv = 0;

	for (auto el : in)
		if (maxv < el) maxv = el;

	return maxv;
}

int modY (int y) {
	if (y < 0) return y + sizeY;
	else if (y >= sizeY) return y - sizeY;
	return y;
}

int modX (int x) {
	if (x < 0) return x + sizeX;
	else if (x >= sizeX) return x - sizeX;
	return x; 
}

int corresp(int cy, int cx) {
	double angle;

	if (cx) {
		angle = double(cy) / double(cx);
		angle = atan(abs(angle)) * 180 / 3.14;
	} else angle = 90;

	if (cy >= 0) {
		if (cx >= 0) angle = 90 - angle;
		else angle += 270;
	} else {
		if (cx >= 0) angle += 90;
		else angle = 270 - angle;
	}

	return int(angle / 360 * 8) * 3 + 1;
}

void makeEpoch (void) {
	std::vector<double> saver;	
	int temp, ly, lx, ty, tx;

	for (int it = 0; it < indvs; ++it) {
		// choice assignment ----------------------------------
		--pops[it].state;
		
		saver = std::vector<double>(24, bado);	
		light = bado;

		for (int y = -zoom; y <= zoom; ++y)
			for (int x = -std::min(zoom - y, y + zoom); sqrt(pow(x, 2) + pow(y, 2)) <= zoom; ++x) {
				ty = modY(pops[it].y + y);
				tx = modX(pops[it].x + x);

				if (status[ty][tx] && ty != pops[it].y && tx != pops[it].x) {
					int iter = corresp(-y, x);
					
					if (status[ty][tx] <= indvs) 
						saver[iter] = perf;	
					else if (status[ty][tx] == indvs + 1)
						saver[iter] = 
							std::max(good + (good - notb) * (double(1) - sqrt(pow(ty - pops[it].y, 2) * pow(tx - pops[it].x, 2)) / zoom), saver[iter]);
					else
						saver[iter] = 
							std::max(bado / 10, saver[iter]);

					light = std::max(saver[iter], light);
				}
			}

		pops[it].soul.dropOut();
		pops[it].soul.setIn(saver, 0, 0);
		pops[it].soul.exec(true, pow(light, 2));
		saver = pops[it].soul.getOut();
		pops[it].soul.setIn(saver, 1, 0);
		
		pops[it].soul.dropOut(); 
		pops[it].soul.dropPart(pow(light, 2));
		
		getChoise(saver);
		status[pops[it].y][pops[it].x] = 0;
		
		ly = pops[it].y;
		lx = pops[it].x;

		if (saver[pops[it].dpos[0]] == 1) --pops[it].y;
		else if (saver[pops[it].dpos[1]] == 1) { --pops[it].y; ++pops[it].x; }
		else if (saver[pops[it].dpos[2]] == 1) ++pops[it].x;
		else if (saver[pops[it].dpos[3]] == 1) { ++pops[it].y; ++pops[it].x; }
		else if (saver[pops[it].dpos[4]] == 1) ++pops[it].y;
		else if (saver[pops[it].dpos[5]] == 1) { ++pops[it].y; --pops[it].x; }
		else if (saver[pops[it].dpos[6]] == 1) --pops[it].x;
		else if (saver[pops[it].dpos[7]] == 1) { --pops[it].y; --pops[it].x; }

		pops[it].y = modY(pops[it].y);
		pops[it].x = modX(pops[it].x);

		if (status[pops[it].y][pops[it].x] == indvs + 2) {
			variety -= 4;

			pops[it].y = ly; 
			pops[it].x = lx;
			
			pops[it].soul.dropPart(1);
			--pops[it].state;
		} else if (status[pops[it].y][pops[it].x] == indvs + 1) {
			variety += 2;
			
			pops[it].state += heal;
			if (pops[it].state > topheal) pops[it].state = topheal;

			--curme;
		} else if (status[pops[it].y][pops[it].x]) {
			variety += 3;
			
			pops[it].state = topheal;
			temp = status[pops[it].y][pops[it].x] - 1;

			reInitId(temp);
			pops[temp].soul = pops[it].soul;
			
			for (int ti = 0; ti < 8; ++ti)
				pops[temp].dpos[ti] = pops[it].dpos[ti];
		}

		status[pops[it].y][pops[it].x] = it + 1;
		
		if (pops[it].state < 1) {
			variety -= 10;
			status[pops[it].y][pops[it].x] = 0;
			reInitId(it);
		}

		// data collecting ------------------------------------
		++curvar;
		if (curvar >= varlen) {
			printf("%f\n", double(variety) / varlen * 1000); 
			variety = 0;
			curvar = 0;
		}
	}

	reInitMe();
}
