! Jacob Purcell

        program popg
        implicit none

                real*8 :: N, g, b, o, R, C
                integer :: t

                !!! data files
                open (unit = 1, file = "./DATA/ndrb.dat") !part b, N no death rate
                open (unit = 2, file = "./DATA/ndrc.dat") !part c, N no death rate
                open (unit = 3, file = "./DATA/wdrd.dat") !part d, N with death rate
                open (unit = 4, file = "./DATA/dndtb.dat") !part b, R no death rate
                open (unit = 5, file = "./DATA/dndtc.dat") !part c, R no death rate
                open (unit = 6, file = "./DATA/dndtd.dat") !part d, R with death rate
                open (unit = 7, file = "./DATA/dndt.dat") ! points from analytic solution for R(t) = 0

                g = 0.03 ! gamma, birth rate
                o = 1.0E5 ! N_0, initial population size
                b = 4.0E-8 ! beta, death rate

                C = o*b / (o*b - g) !as defined in eq5
!!!!!!!!!!!!!!!!!!!!!!!!!
    !!part b COMPLETE
                do t = 0,1000
                    N = o*exp(g*t*0.1) !population, eq3
                    R = g*N !activity
                    write(1,*) t*0.1, N
                    write(4,*) t*0.1, R
                end do
!!!!!!!!!!!!!!!!!!!!!!!!
    !!part c
                do t = 0,50
                    N = o*exp(g*t*2) !population, eq3
                    R = g*N !activity
                    write(2,*) t*0.1, N
                    write(5,*) t*0.1, R
                end do
!!!!!!!!!!!!!!!!!!!!!!!!
    !!part d
                do t = 0,1000
                    N = g*C*exp(g*t*0.1)/(b*(C*exp(g*t*0.1)-1))  !population, eq5
                    R = g*N + b*N*N !activity
                    write(3,*) t*0.1, N
                    write(6,*) t*0.1, R
                end do

                ! R(t) = 0 as defined eq6
                N = g/b
                do t = 0,1000
                    write(7,*) t*0.1, N
                end do

        end program popg
