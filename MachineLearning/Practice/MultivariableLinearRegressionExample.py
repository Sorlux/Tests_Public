def calculatingGradients(x,y,w,b,m):
  
  m,n = x.shape # number of features
  dj_dw = np.zeros((n,))
  dj_db = 0
  for i in range (m):
    inner = (np.dot(x[i],w) + b) - y[i] # Only change for b is dot product for J instead of multiplication
    
    for j in range(n): # Change is that the multiplication needs to now include more than one feature
      dj_dw[j] += inner * x[i,j]
    
  dj_db *= 1/m
  dj_dw *= 1/m #this works because it is just scalar multiplication (numpy supports this)
  return dj_db,dj_dw


def gradientDescentFunction(x,y,w,b,m,iterations,alpha):
  for i in range(iterations):
    dj_db, dj_dw = calculatingGradients(x,y,w,b,m)
    w = w - alpha*dj_dw # This works because it is just scalar multiplcation
    b = b- alpha*dj_db
  return w,b


def predict(x,w,b):
  return np.dot(x,w) + b


def costFunction(x,y,w,b,m):
  cost = 0
  for i in range(m):
    cost += ((np.dot(x[i],w) + b)-y[i])**2 # whenever you do a dot product between x and w, you need to turn x into a vector from a matrix
  cost *= (1/(2*m))
  return cost


xTrain = np.array( [[2104,5,1,45],[1416,3,2,40],[852,2,1,35]])
yTrain = np.array([460,232,178])
b_init = 785.1811367994083
w_init = np.array([ 0.39133535, 18.75376741, -53.36032453, -26.42131618])
m = xTrain.shape[0]
print(costFunction(xTrain,yTrain,w_init,b_init,m))
w,b = gradientDescentFunction(xTrain,yTrain,w_init,b_init,m,1000,0.0000001) # If alpha is too big you get an overflow error
print(w)
print(b)
print(costFunction(xTrain,yTrain,w,b,m))
