function dna = gera_populacao(qtd_ind, tam_dna, limites)

dna = zeros(qtd_ind, tam_dna);

for i = 1 : tam_dna
    dna(:, i) = (limites(1, i) - limites(2, i)) * rand(qtd_ind, 1) + limites(2, i);
end

end