#!/bin/bash

wc -l `find | grep -i \.h$` `find | grep -i \.java$` `find | grep -i \.c$`
