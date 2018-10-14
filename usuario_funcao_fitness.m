function [fitness, I, S] = usuario_funcao_fitness(dna, P)

X = dna(1 : P.objetivo);
Y = dna((P.objetivo + 1) : end);
Lab = (1 : P.objetivo) - 1;

I = 0;
S = 0;

if P.flag_imprimir ~= 0
    if P.flag_imprimirPts ~= 0
        [fitness, I, S] = VORONOI_COLORIDO(double(X') * P.escala, double(Y') * P.escala, double(Lab'), [P.M * P.escala, P.N * P.escala, P.objetivo, P.imprimir, P.imprimirPts], double(P.VimESQ));
    else
        [fitness, I] = VORONOI_COLORIDO(double(X') * P.escala, double(Y') * P.escala, double(Lab'), [P.M * P.escala, P.N * P.escala, P.objetivo, P.imprimir, P.imprimirPts], double(P.VimESQ));
    end
else
    fitness = VORONOI_COLORIDO(double(X'), double(Y'), double(Lab'), [P.M, P.N, P.objetivo, P.imprimir, P.imprimirPts], double(P.Vim));
end

end

