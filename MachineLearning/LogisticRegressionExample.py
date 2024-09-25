def compute_cost_logistic(x,y,w,b):


  m = x.shape[0]
  cost = 0

  for i in range(m):
    z = np.dot(w,x[i]) + b # Calculate Z for the current feature
    g = 1/(1+np.exp(-z)) # Calculate your prediction for the currrent feature
    cost += -y[i] * np.log(g) - (1 - y[i]) * np.log(1-g) # Cost function
  
  cost *= 1/m
  return cost

def compute_gradient_logistic(x,y,w,b):
  m,n = x.shape # m is number of training points, n is number of features
  dj_dw = np.zeros((n,))
  dj_db = 0

for i in range(m):
  z = np.dot(w,x[i]) + b
  g = 1/(1+np.exp(-z))
  inner = g - y[i]
  dj_db += inner
  for j in range (n):
    dj_dw[j] += inner * x[i,j]

dj_db *= 1/m
dj_dw *= 1/m

return dj_db,dj_dw
def gradient_descent(x,y,w,b,alpha,iterator):

m = x.shape[0]

for i in range(iterator):
  dj_db,dj_dw = compute_gradient_logistic(x,y,w,b)
  w = w - alpha*dj_dw
  b = b- alpha*dj_db

return w,b

def prediction(x,w,b):
m, n = x.shape   
p = np.zeros(m)
 
for i in range(m):   
    z = np.dot(x[i], w) + b
    f_wb = 1/(1+np.exp(-z))
    
    # Apply the threshold
    if f_wb > 0.5:
        p[i] = 1
    else:
        p[i] = 0
      
return p

def regularizationCost(x,y,w,b,lambda_ = 1):
  m, n = x.shape
  
  # Calls the compute_cost function that you implemented above
  cost_without_reg = compute_cost_logistic(x, y, w, b) 
  

  reg_cost = 0.
  
  for i in range (n):
      reg_cost += (w[i])**2
  reg_cost *= lambda_/(2*m)
  
  # Add the regularization cost to get the total cost
  total_cost = cost_without_reg + reg_cost

  return total_cost


xTrain = np.array([[0.5, 1.5], [1,1], [1.5, 0.5], [3, 0.5], [2, 2], [1, 2.5]])  #(m,n)
yTrain = np.array([0, 0, 0, 1, 1, 1])


w = np.array([0,0])
b = 0

w,b = gradient_descent(xTrain,yTrain,w,b,0.1,10000)
print(w)
print(b)
xTest = np.array([[0.25, 0.5], [2,2.75], [2.5, 1.5]])
p = prediction(xTest,w,b) # Prediction for the test data based on the model tuned to the training set
print(p)
