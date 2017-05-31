#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define N 65536

typedef float real;

typedef struct {
    real Re;
    real Im;
} complex;

#ifndef PI
#define PI 3.14159265358979323846264338327950288
#endif

int from;
int to;

/* Print original vector into a .txt file. */
static void print_vectorOrig(const char *title, complex *x, int n) {

    int i;
    FILE *fp;
    fp = fopen("C:\\Orig.txt", "w"); // "w" means that we are going to write on this file
    fprintf(fp, "%s (dim=%d):", title, n);
    for (i = 0; i < n; i++) fprintf(fp, " %f + %fi ", x[i].Re, x[i].Im);
    fclose(fp);
    putchar('\n');
    return;
}

/* Print FFT vector into a .txt file. */
static void print_vectorFFT(const char *title, complex *x, int n) {

    int i;
    FILE *fft;
    fft = fopen("C:\\FFT.txt", "w"); // "w" means that we are going to write on this file
    fprintf(fft, "%s (dim=%d):", title, n);
    for (i = 0; i < n; i++) fprintf(fft, "%f + %fi ", x[i].Re, x[i].Im);
    fclose(fft);
    putchar('\n');
    printf("FFT Done\n");
    return;
}

/* Print second FFT calculation to calculate inverse vector into a .txt file. */
static void print_vectorFFT2(const char *title, complex *x, int n) {

    int i;
    FILE *fft2;
    fft2 = fopen("C:\\FFT2.txt", "w"); // "w" means that we are going to write on this file
    fprintf(fft2, "%s (dim=%d):", title, n);
    for (i = 0; i < n; i++) fprintf(fft2, "%f + %fi ", x[i].Re, x[i].Im);
    fclose(fft2);
    putchar('\n');
    printf("FFT2 Done\n");
    return;
}

/* Print filtered vector into a .txt file. */
static void print_filtered(const char *title, complex *x, int n) {

    int i;
    FILE *filtered;
    filtered = fopen("C:\\filtered.txt", "w"); // "w" means that we are going to write on this file
    fprintf(filtered, "%s (dim=%d):", title, n);
    for (i = 0; i < n; i++) fprintf(filtered, "%f + %fi ", x[i].Re, x[i].Im);
    fclose(filtered);
    putchar('\n');
    return;
}

/* Print conjugate of the filtered vector into a .txt file. */
static void print_conjugate(const char *title, complex *x, int n) {

    int i;
    FILE *conjugate;
    conjugate = fopen("C:\\conjugate.txt", "w"); // "w" means that we are going to write on this file
    fprintf(conjugate, "%s (dim=%d):", title, n);
    for (i = 0; i < n; i++) fprintf(conjugate, "%f + %fi ", x[i].Re, x[i].Im);
    fclose(conjugate);
    putchar('\n');
    return;
}

/* Print iFFT vector into a .txt file. */
static void print_iFFT(const char *title, complex *x, int n) {

    int i;
    FILE *iFFT;
    iFFT = fopen("C:\\iFFT.txt", "w"); // "w" means that we are going to write on this file
    fprintf(iFFT, "%s (dim=%d):", title, n);
    for (i = 0; i < n; i++) fprintf(iFFT, "%f ", x[i].Re);
    fclose(iFFT);
    putchar('\n');
    return;
}

/* Calculate FFT. */
void fft(complex *v, int n, complex *aux) {

    if (n > 1) { /* otherwise, do nothing and return */
        int u, i;
        complex z, y, *vo, *ve;
        ve = aux;
        vo = aux + n / 2;
        for (u = 0; u < n / 2; u++) {
            ve[u] = v[2 * u];
            vo[u] = v[2 * u + 1];
        }
        fft(ve, n / 2, v); /* FFT on even-indexed elements of v[] */
        fft(vo, n / 2, v); /* FFT on odd-indexed elements of v[] */
        for (i = 0; i < n / 2; i++) {
            y.Re = cos(2 * PI * i / (double) n);
            y.Im = -sin(2 * PI * i / (double) n);
            z.Re = y.Re * vo[i].Re - y.Im * vo[i].Im;
            z.Im = y.Re * vo[i].Im + y.Im * vo[i].Re;
            v[i].Re = ve[i].Re + z.Re;
            v[i].Im = ve[i].Im + z.Im;
            v[i + n / 2].Re = ve[i].Re - z.Re;
            v[i + n / 2].Im = ve[i].Im - z.Im;
        }
    }
    return;
}

/* Calculate FFT filter. */
void filter(complex *v, int n, int from, int to) {
    int i;
    int counter = 0;

    for (i = from - 1; i < to; i++) {
        v[i].Im = 0;
        v[i].Re = 0;
        v[N - from - counter].Im = 0;
        v[N - from - counter].Re = 0;

        counter++;
    }

    printf("Filtering has been applied\n");

}

/* Calculate FFT conjugate. */
void conjugate(complex *v, int n) {
    int i;

    for (i = 0; i < N; i++) {
        v[i].Im = -v[i].Im;
        v[i].Re = v[i].Re;
    }

    printf("Conjugate has been applied\n");

}

/* Make the final operation to calculate iFFT. */
void iFFT(complex *v, int n) {
    int i;

    for (i = 0; i < N; i++) {
        v[i].Im = 0;
        v[i].Re = (v[i].Re) / N;
    }

    printf("iFFT Done\n");

}

int main(void) {
    complex v[N], aux[N];
    complex v1[N];
    FILE *file;
    
    int value;
    printf("Select the example you want to make FFT and iFFT to:\n"
            "  1.Remove laugh from chainsaw + laugh\n"
            "  2.Remove high frequency from  bark + high frequency\n"
            "  3.Remove flute from guitar + flute\n"
            "  4.Remove bass from crowd + bass\n"
            "  5.Remove phone from mosquito + phone\n");
    scanf("%d", &value);
    if(value==1){
        file = fopen("C:\\chainAndLaugh.txt", "r");
        from = 800;
        to = 4050;
    }
    if(value==2){
        file = fopen("C:\\dogAndFreq.txt", "r");
        from = 2000;
        to = 9000;
    }
    if(value==3){
        file = fopen("C:\\fluteAndGuitar.txt", "r");
        from = 560;
        to = 4000;
    }
    if(value==4){
        file = fopen("C:\\crowdAndBass.txt", "r");
        from = 60;
        to = 1000;
    }
    if(value==5){
        file = fopen("C:\\mosqAndPhone.txt", "r");
        from = 3000;
        to = 32700;
    }
    


    
    
    //Read Values from File to Array
    int i = 0;
    float num;
    while (fscanf(file, "%f", &num) > 0.0) {
        v[i].Re = num;
        v[i].Im = 0;
        i++;

    }
    fclose(file);


    /* Original and FFT */
    print_vectorOrig("Orig", v, N);
    fft(v, N, aux);
    print_vectorFFT("FFT", v, N);

    //Copy of v[i]
    for (i = 0; i < N; i++) {
        v1[i].Im = v[i].Im;
        v1[i].Re = v[i].Re;
    }

    //Filter
    filter(v1, N, from, to);
    print_filtered("FFT Filtered", v1, N);

    //Conjugate
    conjugate(v1, N);
    print_conjugate("Conjugate", v1, N);
    
    
    //INVERSE
    //2nd FFT to calculate inverse
    fft(v1, N, aux);
    print_vectorFFT2("FFT2", v1, N);

    //2nd Conjugate to calculate inverse
    conjugate(v1, N);
    print_conjugate("Conjugate", v1, N);

    //Final operation to calculate inverse
    iFFT(v1, N);
    print_iFFT("iFFT", v1, N);

    exit(EXIT_SUCCESS);
}