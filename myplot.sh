#!/bin/sh

gnuplot <<EOF
	set terminal pdf;
	set output 't.pdf';
	set key off;
	set xrange [0:1]; 
	set yrange [0:1];
	plot '$1';
EOF
