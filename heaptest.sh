#! /bin/bash
make
printf '500\n1\nstring one\n35\n1\nstring two\n55\n1\nstring three\n45\n1\nstring four\n5\n1\nstring two\n10\n1\nstring five\n80\n1\nstring six\n20\n1\nstring seven\n70\n4\n3\nstring four\n4\n2\nstring one\n50\n3\nstring two\n4\n4\n2\nstring five\n60\n4\n4\n4\n5\n' | ./useHeap.out