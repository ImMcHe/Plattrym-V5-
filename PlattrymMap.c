#pragma once
#ifndef __PLATTRYM_MAP__
#define __PLATTRYM_MAP__


int mapW,mapH,*mapHeights;
char*map,*biomes,isMallocedMap=0;
#define AIR 0
#define GRASS 1
#define DIRT 2
#define STONE 3
#define WHITESTONE 4
#define ORE 5
#define DIAMOND 6
#define GRAVEL 7
#define PURPLE 8
#define SNOW 9 
#define ICE 10
#define VALLEYGRASS 11
#define VALLEYDIRT 12
#define NORMALGRASS 13
#define NORMALDIRT 14
#define HARDICE 16
#define HARDVALLEY 17
#define NORMALGRAVEL 18
#define ICEORE 23
#define VALLEYORE 24
#define NORMALORE 25
#define ABOMBLVL1 26
#define ABOMBLVL2 27
#define ABOMBLVL3 28
#define ABOMBLVL4 29
#define ABOMBLVL5 30
#define ABOMBLVL6 31
#define ABOMBLVL7 32
const float blr[]={
	.35,
	2.,
	1.,
	1.674,
	8.24,
	2.225,
	3.6,
	.01,
	-2.,
	.4,
	.6,
	3.1,
	1.36,
	2.12,
	1.34,
	1.,
	1.91,
	2.51,
	.05,
	1.,1.,1.,1.,
	3.,
	4.,
	3.1,
	.35,.35,.35,.35,.35,.35,.35
};
const uint powerUpSpawnChances[][6]={
	{
		0,0,0,0,0,0
	},
	{
		50,25,10,10,10,20
	},
	{
		25,10,5,5,5,10
	},
	{
		75,40,60,50,40,100
	},
	{
		200,200,200,200,200,10
	},
	{
		200,100,80,80,70,90
	},
	{
		500,500,500,500,500,10
	},
	{
		0,0,0,0,0,0
	},
	{
		0,0,0,0,0,RAND_MAX/2
	},
	{
		3,3,15,13,3,6
	},
	{
		5,5,20,14,5,10
	},
	{
		20,20,20,20,50,35
	},
	{
		7,5,7,6,50,25
	},
	{
		15,15,15,15,15,15
	},
	{
		10,10,10,10,10,10
	},
	{
		0,0,0,0,0,0
	},
	{
		10,10,50,40,10,10
	},
	{
		10,10,10,10,100,10
	},
	{
		4,4,4,4,4,4
	},
	{
		0,0,0,0,0,0
	},
	{
		0,0,0,0,0,0
	},
	{
		0,0,0,0,0,0
	},
	{
		0,0,0,0,0,0
	},
	{
		0,0,200,200,0,0
	},
	{
		0,0,0,0,400,0
	},
	{
		67,67,67,67,67,67
	},
	{
		0,0,0,0,0,0
	},
	{
		0,0,0,0,0,0
	},
	{
		0,0,0,0,0,0
	},
	{
		0,0,0,0,0,0
	},
	{
		0,0,0,0,0,0
	},
	{
		0,0,0,0,0,0
	},
	{
		0,0,0,0,0,0
	},
	{
		RAND_MAX,0,0,0,0,0
	},
	{
		0,RAND_MAX,0,0,0,0
	},
	{
		0,0,RAND_MAX,0,0,0
	},
	{
		0,0,0,RAND_MAX,0,0
	},
	{
		0,0,0,0,RAND_MAX,0
	},
	{
		0,0,0,0,0,RAND_MAX
	},
	{
		0,0,0,0,0,0
	},
	{
		0,0,0,0,0,0
	}
};


static inline float getBlr(char type)
{
	if(type<33)
		return blr[type];
	return 1.F;
}


static inline char*getMap(int x,int y)
{
	if(y<0||y>=mapH)
		return map+(mapW*mapH+1);
	return map+((x%mapW+mapW)%mapW*mapH+y);
}


static inline void mallocMap(uint mapWidth,uint mapHeight)
{
	srand(clock());
	if(isMallocedMap)
		isMallocedMap=0,free(map),free(biomes),free(mapHeights);
	map=(char*)malloc(mapWidth*mapHeight+1);
	biomes=(char*)malloc(mapWidth);
	mapHeights=(int*)malloc(sizeof(int)*mapWidth);

	memset(map,0,mapWidth*mapHeight+1);
	memset(biomes,0,mapWidth);
	memset(mapHeights,0,sizeof(int)*mapWidth);

	mapW=mapWidth,mapH=mapHeight;
	isMallocedMap=1;
}


static inline void generateMapNormal(uint mapWidth,uint mapHeight,uint diamondSpawnHeight,uint dirtHeight,uint gravelSpawnRate,uint diamondSpawnRate,uint oreSpawnRate,uint specialOreSpawnRate)
{
	mallocMap(mapWidth,mapHeight);
	int curHeight=-250;
	//int curHeight=-500;
	int curHeightCh=0;
	char mapType=rand()%4;

	for(uint x=0;x<mapWidth/2;x++)
	{
		if(rand()%99==0)
			mapType=rand()%4;
		if(curHeight>(mapType==1?-151:mapType==2?124:-1))
			curHeight=mapType==1?-151:mapType==2?124:-1,curHeightCh=-1;
		curHeightCh=(curHeightCh<0?-1:curHeightCh==0?rand()%2?1:-1:1)*(rand()%(abs(curHeightCh)+(mapType==2?5:2))==0?abs(curHeightCh)+1:abs(curHeightCh)-1);
		curHeight+=curHeightCh*(mapType==1?3:1);
		mapHeights[x]=curHeight+(mapType==1?150:mapType==2?-125:0);
		biomes[x]=mapType;
	}

	for(uint x=0;x<mapWidth/2;x++)
	{
		double bruh=0;
		for(int i=-5;i<6;i++)
			bruh+=(mapHeights[min(max((int)x+i,0),mapWidth/2-1)])/(1.+(double)abs(i));
		mapHeights[x]=bruh/3.9;
	}
	for(int x=0;x<mapWidth/2;x++)
		mapHeights[mapWidth-x-1]=mapHeights[x],biomes[mapWidth-x-1]=biomes[x];

	for(uint x=0;x<mapWidth;x++)
	{
		//printf("%i %i\n",mapHeights[x],biomes[x]);
		for(int y=0;y<mapHeight;y++)
		{
			int curHeight=mapHeights[x];
			int rndShift=0;
			while(rand()%3)
				rndShift++;
			rndShift=rand()%2?rndShift:-rndShift;
			char mapType=biomes[(((int)x+rndShift)%(int)mapWidth+(int)mapWidth)%(int)mapWidth];

			//Diamond spawn simulation
			if(y<curHeight+(int)dirtHeight+rand()%20-10)
				*getMap(x,y)=rand()%(y+1)==0?
					WHITESTONE:
					rand()%diamondSpawnRate==0&&diamondSpawnHeight>=y?
					rand()%2?
						DIAMOND:
						PURPLE:
					0==rand()%oreSpawnRate?
					ORE:
					0==rand()%specialOreSpawnRate&&mapType!=0?
					(mapType==1?ICEORE:mapType==2?VALLEYORE:mapType==3?NORMALORE:AIR):
					0==rand()%gravelSpawnRate?
					GRAVEL:
					STONE;
			//Dirt spawn simulation
			else if(y<curHeight+(int)mapHeight)
				*getMap(x,y)=rand()%gravelSpawnRate==0?(mapType==0?GRAVEL:mapType==1?HARDICE:mapType==2?HARDVALLEY:mapType==3?NORMALGRAVEL:AIR):(mapType==0?DIRT:mapType==1?ICE:mapType==2?VALLEYDIRT:mapType==3?NORMALDIRT:AIR);
			//Grass spawn simulation
			else if(y==curHeight+(int)mapHeight)
				*getMap(x,y)=mapType==0?GRASS:mapType==1?SNOW:mapType==2?VALLEYGRASS:mapType==3?NORMALGRASS:AIR;
			else
				*getMap(x,y)=AIR;
		}
	}

	for(int i=0;i<mapW;i++)
		mapHeights[i]=mapH+mapHeights[i];
}

#endif
