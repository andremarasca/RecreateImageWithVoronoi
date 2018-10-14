function [retorno, avaliacao] = avaliador(dna, P)

[qtd_ind, ~] = size(dna);

retorno = 0;

avaliacao = zeros(1, qtd_ind);

for i = 1 : qtd_ind
    avaliacao(i) = usuario_funcao_fitness(dna(i, :), P);
end

if min(avaliacao) < 0.1
    retorno = 1;
end

end