% Nawiązanie połączenia

t = tcpserver("0.0.0.0", 12345);
disp("Czekam na połączenie...");
waitfor(t, "Connected", true);
disp("Połączono!");
D = read(t, 1, "double");
kroki = read(t, 1, "double");

% Generowanie odpowiedzi skokowej
obj = [];
for k = 1:D
    u_s = read(t, 1, "double");
    [y, obj] = ObiektMATLAB(obj, u_s);
    write(t, y, "double");
end
disp("Pomyślnie wysłano wektor s.");

% Pętla regulacji
obj = []; % reset obiektu
for k = 1:kroki
    u = read(t, 1, "double");
    [y, obj] = ObiektMATLAB(obj, u);
    write(t, y, "double");
end
disp("Połączenie zakończone powodzeniem.");