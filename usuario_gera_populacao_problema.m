function dna = gera_populacao_problema(objetivo, M, N, qtd_ind)

aresta = sqrt(objetivo);
p = 1 / (aresta - 1);

XXXX = zeros(1, objetivo);
YYYY = zeros(1, objetivo);

u = 1;
for i = 0 : (aresta - 1)
    for j = 0 : (aresta - 1)
        XXXX(u) = (i / (aresta - 1) * (1 - p) + p/2) * M;
        YYYY(u) = (j / (aresta - 1) * (1 - p) + p/2) * N;
        u = u + 1;
    end
end

XX = repmat(XXXX, qtd_ind, 1) + M * p/2 * (2 * rand(qtd_ind, objetivo)-1);
YY = repmat(YYYY, qtd_ind, 1) + N * p/2 * (2 * rand(qtd_ind, objetivo)-1);

dna = [XX, YY];
dna(end, :) = [XXXX, YYYY];

end

