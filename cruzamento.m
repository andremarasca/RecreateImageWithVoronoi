function dna_filho = cruzamento(dna_pai, dna_mae)

    B = rand();
    dna_filho = B * dna_mae + (1 - B) * dna_pai;
    
end

