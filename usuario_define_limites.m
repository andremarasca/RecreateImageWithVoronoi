function limites = usuario_define_limites(P)


lim_up = [(P.M-1) * ones(1, P.objetivo), (P.N-1) * ones(1, P.objetivo)];
lim_dw = [zeros(1, P.objetivo), zeros(1, P.objetivo)];
limites = [lim_up; lim_dw];


end

