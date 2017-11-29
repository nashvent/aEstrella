import numpy as np
np.random.seed(0)
# points = np.array([[0, 0], [0, 1.1], [1, 0], [1, 1]])
tamGrafo=1000
points = np.random.random((tamGrafo, 2))

from scipy.spatial import Delaunay
tri = Delaunay(points)


import matplotlib.pyplot as plt
from matplotlib import collections  as mc
import pylab as pl
from scipy.spatial import distance

rects = [
  [(0.4, 0.4), (0.6, 0.5)], 
  [(0.1, 0.1), (0.9, 0.15)],
  [(0.2, 0.7), (0.3, 0.8)],
  [(0.7, 0.7), (0.8, 0.8)]
#   [(0.2, 0.4), (0.6, 0.8)],
]

def inside(p, r):
  return r[0][0] <= p[0] <= r[1][0] and r[0][1] <= p[1] <= r[1][1]

def remove_edge(p1, p2, rects):
  remove = False
  for r in rects:
    if inside(p1, r) and inside(p2, r):
      remove = True

  return remove


edges = set()
for a, b, c in tri.simplices:
  p1, p2, p3 = points[a], points[b], points[c]

  if not remove_edge(p1, p2, rects):
    edges.add((a, b, distance.euclidean(p1, p2)))
    edges.add((b, a, distance.euclidean(p1, p2))) # podrian eliminar este si lo hacen no direccionado 

  if not remove_edge(p2, p3, rects):
    edges.add((b, c, distance.euclidean(p2, p3)))
    edges.add((c, b, distance.euclidean(p2, p3))) # podrian eliminar este si lo hacen no direccionado 

  if not remove_edge(p3, p1, rects):
    edges.add((c, a, distance.euclidean(p3, p1)))
    edges.add((a, c, distance.euclidean(p3, p1))) # podrian eliminar este si lo hacen no direccionado 



# plt.triplot(points[:,0], points[:,1], tri.simplices.copy())
# plt.plot(points[:,0], points[:,1], 'o')

# dibujar el grafo
lines = []
for e in edges: 
  lines.append([points[e[0]], points[e[1]]])
  
lc = mc.LineCollection(lines, linewidths=1)
fig, ax = pl.subplots()
ax.add_collection(lc)
ax.autoscale()
ax.margins(0.1)

# dibujar los vertices del path
 #path = [543, 471, 988, 687, 165, 843] # vertices del nodo
path = [0,268,958,308,18,549,539,999]
pps = points[path,:]
plt.plot(pps[:,0], pps[:,1], 'o')
plt.show()

 

#  create text file
f = open("grafo"+str(tamGrafo)+".txt",'w')
print len(points), len(edges)
print >>f,len(points), len(edges)
# print vertices
for p in points:
  #print p[0], p[1]
  print >>f,p[0], p[1]

# print aristas
for e in edges:
  #print e[0], e[1], e[2]
  print >>f,e[0], e[1], e[2]
