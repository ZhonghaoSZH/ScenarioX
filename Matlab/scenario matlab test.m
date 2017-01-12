% Read original audio file
[y_or,Fs]=audioread('original.wav');
% Plot time domain graph
L=length(y_or);
T = L/Fs;
t= 1/Fs:1/Fs:T;
figure(1);
plot(t,y_or);
title('time domain original');

% Plot frequency domain graph
[y_or,Fs]=audioread('original.wav');
L=length(y_or);
f=linspace(-Fs/2,Fs/2,L);
Y_or= fft(y_or,L);
figure(2);
plot(f,fftshift(abs(Y_or)));
title('frequency domain original');

% Read scrambled audio file
[y_sc,Fs]=audioread('Secret_message.wav');
% Plot time domain graph
L=length(y_sc);
T = L/Fs;
t= 1/Fs:1/Fs:T;
figure(3);
plot(t,y_sc);
title('time domain scrambled');

% Plot frequency domain graph
[y_sc,Fs]=audioread('Secret_message.wav');
L=length(y_sc);
f=linspace(-Fs/2,Fs/2,L);
Y_sc= fft(y_sc,L);
figure(4);
plot(f,fftshift(abs(Y_sc)));
hold on;
title('frequency domain scrambled');
% Find the highest frequency point
[pk,index] = findpeaks(fftshift(abs(Y_sc)),'Npeaks',2,'SortStr','descend')
plot(f(index),pk,'or')
hold off;
%filter out 7900Hz to 8100Hz
d  = fdesign.bandstop('N,Fp1,Fp2,Ap', 2, 7700, 8200, 1, Fs);
bandstop = design(d, 'cheby1');
scr_y_scr = filter(bandstop, y_sc);
%plot the descrambled wav in frequency domain
YY_sc= fft(scr_y_scr,L);
figure(5);
plot(f,fftshift(abs(YY_sc)));
sound(scr_y_scr, Fs)
% Read original audio file
[y_or,Fs]=audioread('original.wav');
% Plot time domain graph
L=length(y_or);
T = L/Fs;
t= 1/Fs:1/Fs:T;
figure(1);
plot(t,y_or);
title('time domain original');

% Plot frequency domain graph
[y_or,Fs]=audioread('original.wav');
L=length(y_or);
f=linspace(-Fs/2,Fs/2,L);
Y_or= fft(y_or,L);
figure(2);
plot(f,fftshift(abs(Y_or)));
title('frequency domain original');

% Read scrambled audio file
[y_sc,Fs]=audioread('scrambled.wav');
% Plot time domain graph
L=length(y_sc);
T = L/Fs;
t= 1/Fs:1/Fs:T;
figure(3);
plot(t,y_sc);
title('time domain scrambled');

% Plot frequency domain graph
[y_sc,Fs]=audioread('scrambled.wav');
L=length(y_sc);
f=linspace(-Fs/2,Fs/2,L);
Y_sc= fft(y_sc,L);
figure(4);
plot(f,fftshift(abs(Y_sc)));
hold on;
title('frequency domain scrambled');
% Find the highest frequency point
[pk,index] = findpeaks(fftshift(abs(Y_sc)),'Npeaks',2,'SortStr','descend')
plot(f(index),pk,'or')
hold off;
%filter out 7900Hz to 8100Hz
d  = fdesign.bandstop('N,Fp1,Fp2,Ap', 2, 7700, 8200, 1, Fs);
bandstop = design(d, 'cheby1');
scr_y_scr = filter(bandstop, y_sc);
%plot the descrambled wav in frequency domain
YY_sc= fft(scr_y_scr,L);
figure(5);
plot(f,fftshift(abs(YY_sc)));
sound(scr_y_scr, Fs)

for n= 1:8
   taylor(y,x,'Order',n)
end
syms x y
x = linspace(1,180,180)
y = x*(2*pi/360)
x = 1.12*sin(y)-y
y = linspace(1,180,180)
plot(y,x)

eqn2 = 'D2y + 6*Dy + 3*y = 24*exp(-2*t)';
inits2 = 'y(0)=3, Dy(0)=6';
y=dsolve(eqn2,inits2,'t')
y= 1/65*cos(x)+8/65*sin(x)+(-1/130+53/1820*14^(1/2))*exp((-4+14^(1/2))*x) -1/1820*(53+14^(1/2))*14^(1/2)*exp(-(4+14^(1/2))*x)
z = eval(vectorize(y)); 
plot(x,z)

eqn2 = '2*Dy + 7*y = 9*exp(-5*t)';
inits2 = 'y(0)=8';
y=dsolve(eqn2,inits2,'t')
y= 1/65*cos(x)+8/65*sin(x)+(-1/130+53/1820*14^(1/2))*exp((-4+14^(1/2))*x) -1/1820*(53+14^(1/2))*14^(1/2)*exp(-(4+14^(1/2))*x)
z = eval(vectorize(y)); 
plot(x,z)



eqn2 = '5*Dy + 6*y = 3*exp(-4*t)';
inits2 = 'y(0)=1';
y=dsolve(eqn2,inits2,'t')

