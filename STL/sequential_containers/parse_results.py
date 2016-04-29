#!/usr/bin/env python3
import os
import collections
import re
# where to search for test output files
base = 'output_dir'

# where to store graphs
img_dir='img'

tests=collections.defaultdict(dict)
xmax=0
for rf in os.listdir(base):
    size=int(rf.split('_')[-1])
    if size > xmax:
        xmax=size
    with open(base+'/'+rf) as f:
        data = [l.strip() for l in f.readlines() if len(l) > 2]
    if not data:
        print(rf)
        continue
    data[0] = data[0].split(str(size))[1]
    for line in data:
        m = re.match(r'^(?P<name>[a-z]+)(?P<num>[0-9.e\-]+)s$', line)
        if not m:
            test_name = line
        else:
            if m.group('name') not in tests[test_name]:
                tests[test_name][m.group('name')] = collections.defaultdict(dict)
            tests[test_name][m.group('name')][size]=float(m.group('num'))

import matplotlib.pyplot as pp
# Generate images for each test
for name, test in tests.items():
    idx = 1
    pp.subplots(nrows=len(test), ncols=1, figsize=(8,15), squeeze=False)
    pp.suptitle(name)
    for coll, data in sorted(test.items(), key=lambda x:x[0]):
        pp.subplot(len(test),1,idx)
        x=sorted(data.keys())
        y=[data[k] for k in x]
        pp.plot(x,y)
        pp.title(coll)
        pp.ylabel('time (s)')
        idx += 1
        pp.xlim([0, xmax])
        pp.subplots_adjust(hspace=1.2)
        pp.locator_params(axis='y', nbins=5)
    pp.savefig('{}/{}.png'.format(img_dir,name))
    pp.clf()


#generate images for each container type
colls=list(tests[list(tests.keys())[0]].keys())
for coll in colls:
    idx=1
    pp.subplots(nrows=len(tests), ncols=1, figsize=(8,15), squeeze=False)
    pp.suptitle(coll)
    for name, test in sorted(tests.items(), key=lambda x:x[0]):
        data = test[coll]
        pp.subplot(len(tests),1,idx)
        x=sorted(data.keys())
        y=[data[k] for k in x]
        pp.plot(x,y)
        pp.title(name)
        idx += 1
        pp.xlim([0, xmax])
        pp.subplots_adjust(hspace=1.2)
        pp.locator_params(axis='y', nbins=5)
    pp.savefig('{}/{}.png'.format(img_dir,coll))
    pp.clf()

