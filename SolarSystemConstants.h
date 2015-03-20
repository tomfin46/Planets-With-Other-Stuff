// PI
const GLfloat PI = 3.1415926535;

// Lighting
const GLfloat LIGHT0_POSITION[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat LIGHT_AMBIENT[]	 = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat LIGHT_DIFFUSE[]	 = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat LIGHT_SPECULAR[]	 = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat LIGHT_EMISSION[]	 = { 1.0f, 1.0f, 1.0f, 0.0f };
const GLfloat DEFAULT_EMISSION[] = { 0.0f, 0.0f, 0.0f, 1.0f };

// Viewer
const GLfloat MAXIMUM_VIEWER_DISTANCE    = 320;
const GLfloat MINIMUM_VIEWER_DISTANCE    = 1;
const GLfloat INITIAL_VIEWER_DISTANCE    = 40;
const GLfloat VIEWER_DISTANCE_INCREMENT  = 1;
const GLfloat INITIAL_VIEWER_AZIMUTH     = 0.0;
const GLfloat INITIAL_VIEWER_ZENITH      = PI / 2.0;
const GLfloat VIEWER_ANGLE_INCREMENT     = PI / 60.0;

// Positioning
const GLint INIT_WINDOW_POSITION[2] = { 50, 50 };
const GLfloat ASPECT_RATIO = 1.5;
const GLfloat INITIAL_LOOK_AT_POSITION[] = { 0.0, 0.0, 0.0 };

// Skybox
const char SKYBOX[] = "Bitmaps/Skybox/skyboxgreenhuge.bmp";
const GLfloat SKYBOX_OFFSET = 100;

/******************************************************/
/*                  Planetary Bodies                  */
/*                                                    */
/*                RADIUS = Mean Radius                */
/*       ORBIT_RADIUS = Semi-Major Axis (in AU)       */
/*       ORBIT_DUR = Orbital Period (in days)         */
/* ROTATION_DUR = Sidereal Rotation Period (in days)  */
/* INCLINATION = Inclination (to Ecliptic in degrees) */
/******************************************************/

// Scaling Constants
const GLfloat AU_CONST = 14.9;
const GLfloat RADIUS_CONST = 0.63781;

/*****************			Sun			**********************/
const char SUN_IMG[] = "Bitmaps/sunmap.bmp";
const GLfloat SUN_RADIUS = 20;
const GLfloat SUN_RADIUS_OFFSET = RADIUS_CONST * SUN_RADIUS;
/************************************************************/

/*****************		  Mercury		*********************/
const GLuint MERCURY = 1;
const char MERCURY_IMG[] = "Bitmaps/mercurymap.bmp";
const GLfloat MERCURY_RADIUS = 0.38;
const GLfloat MERCURY_ORBIT_RADIUS = 0.387;
const GLfloat MERCURY_ORBIT_DUR = 88.0;
const GLfloat MERCURY_ROTATION_DUR = 58.6;
const GLfloat MERCURY_INCLINATION = 7.01;
/************************************************************/

/*****************			Venus		*********************/
const GLuint VENUS = 2;
const char VENUS_IMG[] = "Bitmaps/venusmap.bmp";
const GLfloat VENUS_RADIUS = 0.95;
const GLfloat VENUS_ORBIT_RADIUS = 0.723;
const GLfloat VENUS_ORBIT_DUR = 224.7;
const GLfloat VENUS_ROTATION_DUR = -243.0;
const GLfloat VENUS_INCLINATION = 3.39;
/************************************************************/

/*****************			Earth		*********************/
const GLuint EARTH = 3;
const char EARTH_IMG[] = "Bitmaps/earthmap.bmp";
const GLfloat EARTH_RADIUS = 1;           //in km
const GLfloat EARTH_ORBIT_RADIUS = 1;  //in km
const GLfloat EARTH_ORBIT_DUR = 365;
const GLfloat EARTH_ROTATION_DUR = 1.0;
const GLfloat EARTH_INCLINATION = 7.155;
		/****************/
		/*  Earh's Moon */
		/****************/
		const GLuint MOON = 31;
		const char MOON_IMG[] = "Bitmaps/Moons/moonmap.bmp";
		const GLfloat MOON_RADIUS = 0.273;
		const GLfloat MOON_ORBIT_RADIUS = 0.00257;
		const GLfloat MOON_LUNAR_CYCLE = 27.3;
		const GLfloat MOON_INCLINATION = 5;
/************************************************************/

/*****************			Mars		*********************/
const GLuint MARS = 4;
const char MARS_IMG[] = "Bitmaps/marsmap.bmp";
const GLfloat MARS_RADIUS = 0.53;
const GLfloat MARS_ORBIT_RADIUS = 1.52;
const GLfloat MARS_ORBIT_DUR = 686;
const GLfloat MARS_ROTATION_DUR = 1.02;
const GLfloat MARS_INCLINATION = 1.85;
		/*****************/
		/*  Mars' Moons  */
		/*****************/
		//Phobos
		const char PHOBOS_IMG[] = "Bitmaps/Moons/phobosmap.bmp";
		const GLfloat PHOBOS_RADIUS = 0.04;
		const GLfloat PHOBOS_ORBIT_RADIUS = 0.006;
		const GLfloat PHOBOS_LUNAR_CYCLE = 0.32;
		const GLfloat PHOBOS_INCLINATION = 26;

		//Deimos
		const char DEIMOS_IMG[] = "Bitmaps/Moons/deimosmap.bmp";
		const GLfloat DEIMOS_RADIUS = 0.02;
		const GLfloat DEIMOS_ORBIT_RADIUS = 0.016;
		const GLfloat DEIMOS_LUNAR_CYCLE = 1.26;
		const GLfloat DEIMOS_INCLINATION = 28;
/************************************************************/

/*****************		  Asteroids			*****************/
const char ASTEROID_IMG[] = "Bitmaps/asteroidmap.bmp";
const GLfloat ASTEROID_ORBIT_DUR = 1679.67;
const GLfloat ASTEROID_RADIUS = 0.152;
const GLfloat ASTEROID_ORBIT_RADIUS[] = {3.5f, 2.1f, 2.9f, 2.3f, 3.8f, 2.0f, 3.0f, 3.9f, 3.6f, 2.7f, 2.2f, 3.3f, 1.9f, 2.6f, 3.7f, 2.4f, 3.1f, 2.5f, 3.2f, 2.8f, 3.4f};
/************************************************************/

/*****************			Jupiter		*********************/
const GLuint JUPITER = 5;
const char JUPITER_IMG[] = "Bitmaps/jupitermap.bmp";
const GLfloat JUPITER_RADIUS = 11.21;
const GLfloat JUPITER_ORBIT_RADIUS = 5.20;
const GLfloat JUPITER_ORBIT_DUR = 4333;
const GLfloat JUPITER_ROTATION_DUR = 0.414;
const GLfloat JUPITER_INCLINATION = 1.31;
		/*********************/
		/*  Jupiter's Moons  */
		/*********************/
		//Io
		const char IO_IMG[] = "Bitmaps/Moons/iomap.bmp";
		const GLfloat IO_RADIUS = 0.286;
		const GLfloat IO_ORBIT_RADIUS = 0.002;
		const GLfloat IO_LUNAR_CYCLE = 1.77;
		const GLfloat IO_INCLINATION = 2;
		//Europa
		const char EUROPA_IMG[] = "Bitmaps/Moons/europamap.bmp";
		const GLfloat EUROPA_RADIUS = 0.245;
		const GLfloat EUROPA_ORBIT_RADIUS = 0.004;
		const GLfloat EUROPA_LUNAR_CYCLE = 3.55;
		const GLfloat EUROPA_INCLINATION = 18;
		//Ganymede
		const char GANYMEDE_IMG[] = "Bitmaps/Moons/ganymedemap.bmp";
		const GLfloat GANYMEDE_RADIUS = 0.413;
		const GLfloat GANYMEDE_ORBIT_RADIUS = 0.007;
		const GLfloat GANYMEDE_LUNAR_CYCLE = 7.15;
		const GLfloat GANYMEDE_INCLINATION = 8;
		//Callisto
		const char CALLISTO_IMG[] = "Bitmaps/Moons/callistomap.bmp";
		const GLfloat CALLISTO_RADIUS = 0.378;
		const GLfloat CALLISTO_ORBIT_RADIUS = 0.013;
		const GLfloat CALLISTO_LUNAR_CYCLE = 16.7;
		const GLfloat CALLISTO_INCLINATION = 8.5;
/************************************************************/

/*****************			Saturn		*********************/
const GLuint SATURN = 6;
const char SATURN_IMG[] = "Bitmaps/saturnmap.bmp";
const GLfloat SATURN_RADIUS = 9.45;
const GLfloat SATURN_ORBIT_RADIUS = 9.58;
const GLfloat SATURN_ORBIT_DUR = 10759;
const GLfloat SATURN_ROTATION_DUR = 0.411;
const GLfloat SATURN_INCLINATION  = 2.49;
const char SATURN_RINGS_IMG[] = "Bitmaps/saturnringmap.bmp";
		/*******************/
		/*  Saturn's Moon  */
		/*******************/
		//Titan
		const char TITAN_IMG[] = "Bitmaps/Moons/titanmap.bmp";
		const GLfloat TITAN_RADIUS = 0.404;
		const GLfloat TITAN_ORBIT_RADIUS = 0.008;
		const GLfloat TITAN_LUNAR_CYCLE = 15.9;
		const GLfloat TITAN_INCLINATION = 12;
/************************************************************/

/*****************			Uranus		*********************/
const GLuint URANUS = 7;
const char URANUS_IMG[] = "Bitmaps/uranusmap.bmp";
const GLfloat URANUS_RADIUS = 4.007;
const GLfloat URANUS_ORBIT_RADIUS = 19.2;
const GLfloat URANUS_ORBIT_DUR = 30799;
const GLfloat URANUS_ROTATION_DUR = -0.718;
const GLfloat URANUS_INCLINATION  = 0.77;
		/*******************/
		/*  Uranus' Moons  */
		/*******************/
		//Titania
		const char TITANIA_IMG[] = "Bitmaps/Moons/titaniamap.bmp";
		const GLfloat TITANIA_RADIUS = 0.1235;
		const GLfloat TITANIA_ORBIT_RADIUS = 0.003;
		const GLfloat TITANIA_LUNAR_CYCLE = 8.7;
		const GLfloat TITANIA_INCLINATION = 4;
		//Oberon
		const char OBERON_IMG[] = "Bitmaps/Moons/oberonmap.bmp";
		const GLfloat OBERON_RADIUS = 0.1194;
		const GLfloat OBERON_ORBIT_RADIUS = 0.004;
		const GLfloat OBERON_LUNAR_CYCLE = 13.5;
		const GLfloat OBERON_INCLINATION = 0.6;
		//Umbriel
		const char UMBRIEL_IMG[] = "Bitmaps/Moons/umbrielmap.bmp";
		const GLfloat UMBRIEL_RADIUS = 0.092;
		const GLfloat UMBRIEL_ORBIT_RADIUS = 0.002;
		const GLfloat UMBRIEL_LUNAR_CYCLE = 4.1;
		const GLfloat UMBRIEL_INCLINATION = 1;
		//Ariel
		const char ARIEL_IMG[] = "Bitmaps/Moons/arielmap.bmp";
		const GLfloat ARIEL_RADIUS = 0.0908;
		const GLfloat ARIEL_ORBIT_RADIUS = 0.001;
		const GLfloat ARIEL_LUNAR_CYCLE = 2.5;
		const GLfloat ARIEL_INCLINATION = 3;
		//Miranda
		const char MIRANDA_IMG[] = "Bitmaps/Moons/mirandamap.bmp";
		const GLfloat MIRANDA_RADIUS = 0.03697;
		const GLfloat MIRANDA_ORBIT_RADIUS = 0.001;
		const GLfloat MIRANDA_LUNAR_CYCLE = 1.4;
		const GLfloat MIRANDA_INCLINATION = 42;
/************************************************************/

/*****************			Neptune		*********************/
const GLuint NEPTUNE = 8;
const char NEPTUNE_IMG[] = "Bitmaps/neptunemap.bmp";
const GLfloat NEPTUNE_RADIUS = 3.883;
const GLfloat NEPTUNE_ORBIT_RADIUS = 30.1;
const GLfloat NEPTUNE_ORBIT_DUR = 60190;
const GLfloat NEPTUNE_ROTATION_DUR = 0.671;
const GLfloat NEPTUNE_INCLINATION = 1.77;
		/********************/
		/*  Neptune's Moon  */
		/********************/
		//Triton
		const char TRITON_IMG[] = "Bitmaps/Moons/tritonmap.bmp";
		const GLfloat TRITON_RADIUS = 0.2122;
		const GLfloat TRITON_ORBIT_RADIUS = 0.002;
		const GLfloat TRITON_LUNAR_CYCLE = -5.9;
		const GLfloat TRITON_INCLINATION = 130;
/************************************************************/

/*****************			Pluto		*********************/
const GLuint PLUTO = 9;
const char PLUTO_IMG[] = "Bitmaps/plutomap.bmp";
const GLfloat PLUTO_RADIUS = 0.36;
const GLfloat PLUTO_ORBIT_RADIUS = 39.3;
const GLfloat PLUTO_ORBIT_DUR = 89866;
const GLfloat PLUTO_ROTATION_DUR = -6.39;
const GLfloat PLUTO_INCLINATION = 17;
		/******************/
		/*  Pluto's Moon  */
		/******************/
		//Charon
		const char CHARON_IMG[] = "Bitmaps/Moons/charonmap.bmp";
		const GLfloat CHARON_RADIUS = 0.095;
		const GLfloat CHARON_ORBIT_RADIUS = 0.0001;
		const GLfloat CHARON_LUNAR_CYCLE = 6.4;
		const GLfloat CHARON_INCLINATION = 112;
/************************************************************/