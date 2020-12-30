import numpy as np

n = int(input('numero de vertices:\n'))
vertices = np.arange(n);


arestas = []
arestas1 = []

for i in range(2*n):
    v1 = np.random.randint(0,n)
    while(True):
        
        v2 = np.random.randint(0,n)
        w = np.random.randint(1,10)

        if v1 != v2:
            if  ( not (v1,v2) in arestas) and (not (v2,v1) in arestas):
                arestas.append((v1,v2))
                arestas1.append((v1,v2,w))
                break
            
with open('en_prim.in','w') as file:
    file.write(str(n) + '\n' + str(2*n) + '\n')
    for aresta in arestas1:
        file.write(str(aresta[0]) + ' ' + str(aresta[1]) + ' ' + str(aresta[2]) + '\n')
    
    file.write(str(np.random.randint(0,n)))
