function usuario_ultrapassou_best(P, dna, fitness, geracao)

if P.imprimir ~= 0
    P.flag_imprimir = 1;
end
if P.imprimirPts ~= 0
    P.flag_imprimirPts = 1;
end
[~, I, ~] = usuario_funcao_fitness(dna, P);

P.flag_imprimir = 0;
P.flag_imprimirPts = 0;

if P.imprimirData ~= 0
    frase = sprintf('%s || Gen: %4d || Fit: %4g', datetime('now'), geracao, fitness);
    text_str{1} = frase;
    I = insertText(uint8(I),[0, 0], text_str, 'FontSize',32,'BoxColor', {'black'}, 'BoxOpacity', 0.5, 'TextColor', 'white');
end

if P.gravar == 1
    nome = sprintf('Saida/%04d.png', geracao);
    if ~isempty(P.II)
        imwrite(uint8([P.II,I]), nome);
    else
        imwrite(uint8(I), nome);
    end
end

end

