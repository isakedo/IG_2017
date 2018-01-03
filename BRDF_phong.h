//
// Isak Edo Vivancos - 682405
// BRDF phong
//

class BRDF_phong {

private:

    RGB coeficiente_difuso = RGB(), coeficiente_especular = RGB();
    int brillo = 0;

public:

    BRDF_phong() = default;
    BRDF_phong(const RGB& _coeficiente_difuso, const RGB& _coeficiente_especular
            , const int& _brillo) :
            coeficiente_difuso(_coeficiente_difuso),
            coeficiente_especular(_coeficiente_especular), brillo(_brillo) {}

    const RGB &getKd() const {
        return coeficiente_difuso;
    }

    const RGB &getKs() const {
        return coeficiente_especular;
    }

    float getBrillo() const {
        return brillo;
    }

    float getProb_Kd() const {
        float resultado = fmaxf(coeficiente_difuso.getR(),
           coeficiente_difuso.getG());
        resultado = fmaxf(resultado,coeficiente_difuso.getB());
        return resultado;
    }

    float getProb_Ks() const {
        float resultado = fmaxf(coeficiente_especular.getR(),
                                coeficiente_especular.getG());
        resultado = fmaxf(resultado,coeficiente_especular.getB());
        return resultado;;
    }

    float getInclinacion_Dif(const float& rand) {
        return acosf(sqrtf(1-rand));
    }

    float getAcimut_Dif(const float& rand) {
        return 2 * (float)M_PI * rand;
    }

    float getFactor_Dif() {
        return 1 / getProb_Kd();
    }

    float getInclinacion_Esp(const float& rand) {
        float exp = 1 / ((float)brillo + 1);
        return acosf(powf(rand,exp));
    }

    float getAcimut_Esp(const float& rand) {
        return 2 * (float)M_PI * rand;
    }


    float getFactor_Ref(const Vector& reflejo, const Vector& norm,
                        const Vector& rebote) {
        float cos_inclin_i = norm * rebote;
        float sin_inclin_i = sqrtf(1-powf(cos_inclin_i,2));
        float cos_inclin_r = rebote * reflejo;
        float sin_inclin_r = sqrtf(1-powf(cos_inclin_r,2));
        float factor_num = (brillo + 2) * fabsf(cos_inclin_i)
                           * fabsf(sin_inclin_i);
        float factor_den =  getProb_Ks() * (brillo + 1) * sin_inclin_r;
        return factor_num/factor_den;
    }

};
