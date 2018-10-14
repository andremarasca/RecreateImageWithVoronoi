function S_selection = ini_ExponentialRanking(c, qtd_ind)

    k = (c - 1) / (c^qtd_ind - 1);
    S_selection = zeros(1, qtd_ind);
        
    for i = 2 : qtd_ind
        S_selection(i) = S_selection(i - 1) + k * c^(qtd_ind - i);
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

