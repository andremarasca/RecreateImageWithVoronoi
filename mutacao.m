function dna = mutacao(dna, tam_dna, limites, geracao, geracoes, b)

gene = randi([1 tam_dna],1,1);
if randi([0 1]) == 0
    dna(gene) = dna(gene) + delta_mut(geracao, limites(1, gene) - dna(gene), geracoes, b);
else
    dna(gene) = dna(gene) - delta_mut(geracao, dna(gene) - limites(2, gene), geracoes, b);
end

end

