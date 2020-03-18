import numpy as np 
import scipy.integrate as integrate
import matplotlib.pyplot as plt
from tqdm import tqdm

#參數設定
lamb = 8
alpha = 6
sigma = 1
u = 2


def coverage( T ):
    Pc = lambda r: np.exp(-1*np.pi*lamb*r**2)*np.exp( -1*u*T*r**alpha*sigma**2 )*laplace( T,r )*2*np.pi*lamb*r 
    result, err = integrate.quad( Pc, 0, np.Infinity )
    return result

def laplace( T, r ):
    def first_integral( g ):
        first_integral = lambda v:( 1-np.exp(-u*T*r**alpha*v**(-alpha)*g) )*v
        first_val , err = integrate.quad( first_integral, r, np.Infinity )
        return first_val
    second_integral = lambda g : first_integral( g )*lamb*np.exp(-lamb*g)
    second_val, err = integrate.quad( second_integral, 0, np.Infinity )
    ans = np.exp( -2*np.pi*lamb*second_val )
    return ans 

if __name__ == "__main__":
    T_range = np.linspace( -10, 20, 50 )
    log_range = 10**( T_range/10 )
    C = []
    with tqdm( total = len( log_range ), ascii = True ) as pbar:
        for T in log_range:
            C.append( coverage( T ) )
            pbar.update(1)
    print(C)
    plt.plot( T_range, C )
    plt.xlim(-10,20)
    plt.ylim(0,1)
    plt.yticks(np.arange(0,1,0.1))
    plt.show()





