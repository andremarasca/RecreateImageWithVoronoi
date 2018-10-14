function S_selection = ini_LinearRanking(tx_rep_pior, qtd_ind)

    tx_rep_melhor = 2 - tx_rep_pior;
    S_selection = zeros(1, qtd_ind);

    for i = 2 : qtd_ind
        S_selection(i) = S_selection(i - 1) + ( 1.0 /  qtd_ind) * (tx_rep_pior + (tx_rep_melhor - tx_rep_pior) *   (i - 1) / (qtd_ind - 1));
    end
    
    diff1 = (S_selection(2) - S_selection(1))/2;
    diff2 = (S_selection(end) - S_selection(end-1))/2;
    minimo = S_selection(1);
    maximo = S_selection(end);
    a = ((1 - diff1 -  diff2) / (maximo - minimo));
    b = (diff1 - a * minimo);
    a = a * 32767;
    b = b * 32767;
    
    S_selection = round(a * S_selection + b);
    
end

