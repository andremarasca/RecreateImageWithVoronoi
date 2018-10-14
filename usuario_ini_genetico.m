function [tam_dna, qtd_ind, geracoes, prob_mutacao, fator_mutacao, individuos_salvos] = usuario_ini_genetico(P)

tam_dna = 2 * P.objetivo;
qtd_ind = 100;
geracoes = 500;
prob_mutacao = 60;
fator_mutacao = 1;
individuos_salvos = 3;

end

