close all;
clear all;
clc;


P = usuario_ini_problema;
limites = usuario_define_limites(P);
[tam_dna, qtd_ind, geracoes, prob_mutacao, fator_mutacao, individuos_salvos] = usuario_ini_genetico(P);

% S_selection = ini_LinearRanking(0, qtd_ind); % inicializar vetor de probabilidades
S_selection = ini_ExponentialRanking(0.97, qtd_ind);
% dna = gera_populacao(qtd_ind, tam_dna, limites); % gerar populacao inicial

%%

dna = usuario_gera_populacao_problema(P.objetivo, P.M, P.N, qtd_ind); % gera populacao problema

%%

[retorno, avaliacao] = avaliador(dna, P);
[avaliacao, idx] = sort(avaliacao, 'descend');
dna = dna(idx, :);
idx_avaliacao = 1 : (qtd_ind - individuos_salvos);

%%

geracao = 1;
dna_best = dna(end, :);
fit_best = avaliacao(end);
fprintf('G: %3d | F: %3g | %s\n', geracao, fit_best, datetime('now'));
usuario_ultrapassou_best(P, dna_best, fit_best, geracao);

%%

for geracao = 2 : geracoes
    dna2 = dna;
    for filho = 1 : (qtd_ind - individuos_salvos)
        idx = RankingSelection(S_selection, qtd_ind);
        dna_pai = dna2(idx, :);
        idx = RankingSelection(S_selection, qtd_ind);
        dna_mae = dna2(idx, :);
        dna(filho, :) = cruzamento(dna_pai, dna_mae);
        if randi([1, 100]) < prob_mutacao
            dna(filho, :) = mutacao(dna(filho, :), tam_dna, limites, geracao, geracoes, fator_mutacao);
        end
    end
    [retorno, avaliacao(idx_avaliacao)] = avaliador(dna(idx_avaliacao,:), P);
    [avaliacao, idx] = sort(avaliacao, 'descend');
    dna = dna(idx, :);
    
    if fit_best > avaliacao(end)
        dna_best = dna(end, :);
        fit_best = avaliacao(end);
        fprintf('G: %3d | F: %3g | %s\n', geracao, fit_best, datetime('now'));
        usuario_ultrapassou_best(P, dna_best, fit_best, geracao);
    end
    if retorno == 1
        break;
    end
end