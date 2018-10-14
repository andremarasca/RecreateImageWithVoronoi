function vlinha = delta_mut(t, y, T, b)

r = rand();

vlinha = y * (1 - r^((1 - t / T)*b));

end

