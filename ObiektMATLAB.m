function [y_k1, obj] = ObiektMATLAB(obj, u_k)

    if isempty(obj)
        obj.a = 0.8351;
        obj.b = 0.2713;
        obj.d = 2;
        obj.y_k = 0.0;
        obj.bufor_u = zeros(obj.d + 1, 1);
    end

    obj.bufor_u = [obj.bufor_u(2:end); u_k];
    u_d = obj.bufor_u(1);
    y_k1 = obj.a * obj.y_k + obj.b * u_d;
    obj.y_k = y_k1;
    
end