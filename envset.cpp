namespace env {
	// structures ----------------
	struct unit {
		int x, y, state, dpos[8];
		kernel::model soul;
	};

	// constants ------------------
	const int sizeX = 58,
			  sizeY = 58,
			  step = 13, 
			  mindvs = 100,
			  zoom = 4,
			  heal = 100,
			  topheal = 200,
			  varlen = 10000;
	
	// stimulators ----------------
	const double perf = 1,
				 good = 0.65,
				 notb = 0.3,
				 bado = 0.01;

	// network template -----------
	const auto lays = {
		$(24, {1}),
		$(24, {2}),
		$(37, {3}),
		$(24, {}),
	};

	const double defav = 0.01,
				 reser = 1,
				 neumax = 1,
				 impulse = 1000;
	double light;
	const std::string name = "unit";

	// environment meta data ------ 
	int epoch, aver,
		curme, mes,
		curid, indvs,
		curvar;
	long int variety;
	unit pops[mindvs];

	int status[sizeY][sizeX];

	// environment functions ------
	void init (int indvsI, int medI, int blockI) {
		std::srand(std::time(0));

		for (int it = 0; it < sizeY; ++it) 
			for (int ti = 0; ti < sizeX; ++ti) 
				status[it][ti] = 0;

		int ty = std::rand() % sizeY, tx = std::rand() % sizeX;
		
		mes = curme = medI;
		indvs = curid = indvsI;
		 
		for (int it = 0; it < medI; ++it) {
			while (status[ty][tx]) {
				ty = std::rand() % sizeY;
				tx = std::rand() % sizeX;
			}

			status[ty][tx] = indvs + 1;
		}

		for (int it = 0; it < blockI; ++it) {
			while (status[ty][tx]) {
				ty = std::rand() % sizeY;
				tx = std::rand() % sizeX;
			}

			status[ty][tx] = indvs + 2;
		}
	  
		bool gens[8];
		int pos;
		srand(time(NULL));

		for (int it = 0; it < indvsI; ++it) {

			// creating gene pool
			for (int ti = 0; ti < 8; ++ti)
				gens[ti] = false;

			pos = rand() % 8;

			for (int ti = 0; ti < 8; ++ti) {
				pops[it].dpos[ti] = pos;
				gens[pos] = true;

				pos = (pos + rand() % 7 + 1) % 8;

				while (gens[pos] && ti < 7) { ++pos; pos %= 8; }
			}

			while (status[ty][tx]) {
				ty = std::rand() % sizeY;
				tx = std::rand() % sizeX;
			}

			pops[it].state = topheal;
			pops[it].y = ty;
			pops[it].x = tx;
			status[ty][tx] = it + 1;
			pops[it].soul = kernel::model(lays, defav, reser, neumax, impulse, name);
		}
	}

	void reInitId (int it) {
		int ty = std::rand() % sizeY, tx = std::rand() % sizeX;

		while (status[ty][tx]) {
			ty = std::rand() % sizeY;
			tx = std::rand() % sizeX;
		}
	
		// gene pool rebuild
		bool gens[8];
		int pos;
		
		for (int ti = 0; ti < 8; ++ti)
			gens[ti] = false;

		pos = rand() % 8;

		for (int ti = 0; ti < 8; ++ti) {
			pops[it].dpos[ti] = pos;
			gens[pos] = true;

			pos = (pos + rand() % 7 + 1) % 8;

			while (gens[pos] && ti < 7) { ++pos; pos %= 8; }
		}

		pops[it].state = topheal;
		pops[it].y = ty;
		pops[it].x = tx;
		status[ty][tx] = it + 1; 
		pops[it].soul = kernel::model(lays, defav, reser, neumax, impulse, name);
	}

	void reInitMe (void) {
		int ty = std::rand() % sizeY, tx = std::rand() % sizeX;

		for (; curme < mes; ++curme) {
			while (status[ty][tx]) {
				ty = std::rand() % sizeY;
				tx = std::rand() % sizeX;
			} 
			
			status[ty][tx] = indvs + 1;
		}
	}
};
