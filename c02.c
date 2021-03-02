// On my honor:
//
// - I have not discussed the C language code in my program with
// anyone other than my instructor or the teaching assistants
// assigned to this course.
//
// - I have not used C language code obtained from another student,
// the Internet, or any other unauthorized source, either modified
// or unmodified.
//
// - If any C language code or documentation used in my program
// was obtained from an authorized source, such as a text book or
// course notes, that has been clearly noted with a proper citation
// in the comments of my program.
//
// - I have not designed this program in such a way as to defeat or
// interfere with the normal operation of the Curator System.
//
// Michael Blair
// mblair2000

/*
 * c02.c
 * 
 * Copyright 2021 Michael Blair <mblair2000@localhost.localdomain>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */


#include <stdio.h>

int main(int argc, char** argv)
{
	// set up file input
	char *nameIn = argv[1];
	char *nameOut = argv[2];
	FILE* in = fopen(nameIn, "r");
	FILE* out = fopen(nameOut, "w");
	
	// instantiate real variables, four for each line of text input
	char long1[20], lat1[20], long2[20], lat2[20];
	
	fprintf(out, "\n\n");
	
	// scan the input file to extract information
	while (fscanf(in, "%s %s %s %s", long1, lat1, long2, lat2) == 4)
	{
		// instantiate temp variables to hold information
		int tempLong1deg, tempLong1min, tempLong1sec;
		int tempLong2deg, tempLong2min, tempLong2sec;
		int tempLat1deg, tempLat1min, tempLat1sec;
		int tempLat2deg, tempLat2min, tempLat2sec;
		char tempLongChar1[1], tempLongChar2[1];
		char tempLatChar1[1], tempLatChar2[1];
		
		// get values for longitude of first coordinate
		sscanf(long1, "(%3d%2d%2d%1s,", &tempLong1deg, &tempLong1min, &tempLong1sec, tempLongChar1);
		fprintf(out, "(%03dd %02dm %02ds %1s, ", tempLong1deg, tempLong1min, tempLong1sec, tempLongChar1);
		
		// get values for latitude of first coordinate
		sscanf(lat1, "%2d%2d%2d%1s,", &tempLat1deg, &tempLat1min, &tempLat1sec, tempLatChar1);
		fprintf(out, "%02dd %02dm %02ds %1s)", tempLat1deg, tempLat1min, tempLat1sec, tempLatChar1);
		
		// get values for longitude of second coordinate
		sscanf(long2, "(%3d%2d%2d%1s,", &tempLong2deg, &tempLong2min, &tempLong2sec, tempLongChar2);
		fprintf(out, "	(%03dd %02dm %02ds %1s,", tempLong2deg, tempLong2min, tempLong2sec, tempLongChar2);
		
		// get values for latitude of second coordinate
		sscanf(lat2, "%2d%2d%2d%1s,", &tempLat2deg, &tempLat2min, &tempLat2sec, tempLatChar2);
		fprintf(out, " %02dd %02dm %02ds %1s)", tempLat2deg, tempLat2min, tempLat2sec, tempLatChar2);
		
		
		// difference in each coordinate in total seconds taxi style
		int secsTotLong1 = (tempLong1deg * 3600) + (tempLong1min * 60) + (tempLong1sec);
		int secsTotLat1 = (tempLat1deg * 3600) + (tempLat1min * 60) + (tempLat1sec);
		int secsTotLong2 = (tempLong2deg * 3600) + (tempLong2min * 60) + (tempLong2sec);
		int secsTotLat2 = (tempLat2deg * 3600) + (tempLat2min * 60) + (tempLat2sec);
		int distanceX = abs(secsTotLong1 - secsTotLong2);
		int distanceY = abs(secsTotLat1 - secsTotLat2);
		int distanceSecs = distanceX + distanceY;
		fprintf(out, "   %4d", distanceSecs);
		
		
		// find each difference in coordinates put into normal coords
		int digreesDMS = (int)floor(distanceSecs / 3600);
		int minDMS = (int)floor((distanceSecs - (digreesDMS * 3600)) / 60);
		int secsDMS = distanceSecs % 60;
		fprintf(out, "	%01dd %02dm %02ds\n", digreesDMS, minDMS, secsDMS);
	}
	
	return 0;
}

