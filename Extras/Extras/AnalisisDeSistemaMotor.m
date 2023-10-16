%% Analisis sistema segun datos obtenidos en mediciones de velocidad
pkg load control;
yss=0.3;
ymax=0.33;
tp=1.2;


s=tf('s');
K=yss;
Mp=(ymax-yss)/yss;
psita=sqrt(log(Mp)^2/(pi^2+log(Mp)^2))
wn=pi/(tp*sqrt(1-psita^2))
G=tf(K*wn^2,[1 2*psita*wn wn^2])
step(G)
polos = pole(G)
ceros = zero(G)
ganancia = dcgain(G)


