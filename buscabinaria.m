function idx = buscabinaria(x, n, v)

inicio = 1;
fim = n;

while inicio ~= fim - 1
    meio = floor((inicio + fim)/2);
    if v(meio) < x
        inicio = meio;
    else
        fim = meio;
    end
end

if abs(v(inicio) - x) < abs(v(fim) - x)
    idx = inicio;
else
    idx = fim;
end

end
