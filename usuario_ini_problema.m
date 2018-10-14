function P = usuario_ini_problema

%Imprimir == 0 -> N�o imprimir
%Imprimir == 1 -> Imprimir s� o voronoi
%Imprimir == 2 -> Imprimir Voronoi com contorno branco

imprimir = 1;
imprimirPts = 0;
flag_imprimir = 0;
flag_imprimirPts = 0;
imprimirData = 1;
mostrar = 0;
gravar = 1;

%%

objetivo = 900;

%%

% clear mex
% mex VORONOI_COLORIDO.cpp

%%

nome = sprintf('Saida_%010d', randi([1 10^9], 1, 1));
dir_saida = [pwd, '/Saida'];
if exist(dir_saida)
    comando = ['move "', dir_saida, '" "', [pwd, '/', nome], '"'];
    res = 1;
    while res ~= 0
        res = system(comando);
    end
end

mkdir(dir_saida);

%%

% Imagem em alta resolucao (pode ser ser vazio)
II = imread('Entrada\imHD.png');
II = double(II);
% II = [];
[M, ~, ~] = size(II);
escala = 1080 / M;
if ~isempty(II)
    II = imresize(II, escala);
end

II = uint8(II);

% Imagem Original
I = imread('Entrada\im.png');
I = double(I);
[M, N, L] = size(I);
escala = round(1080 / M);

% escala = 3;

% escala = 1;

%%%%%%%%%%%%%%%%%

Vim = zeros(M * N * L, 1);

u = 1;
for k = 1 : L
    for i = 1 : M
        for j = 1 : N
            Vim(u, 1) = double(I(i, j, k));
            u = u + 1;
        end
    end
end

VimESQ = zeros(M * N * L * escala^2, 1);
IESQ = imresize(I, escala);

u = 1;
for k = 1 : L
    for i = 1 : M * escala
        for j = 1 : N * escala
            VimESQ(u, 1) = double(IESQ(i, j, k));
            u = u + 1;
        end
    end
end

%%%%%%%%%%%%%%%%%

P.I = I;
P.II = II;
P.M = M;
P.N = N;
P.L = L;
P.Vim = Vim;
P.VimESQ = VimESQ;
P.escala = escala;
P.imprimir = imprimir;
P.imprimirPts = imprimirPts;
P.flag_imprimir = 0;
P.flag_imprimirPts = 0;
P.imprimirData = imprimirData;
P.mostrar = mostrar;
P.gravar = gravar;
P.objetivo = objetivo;

end

