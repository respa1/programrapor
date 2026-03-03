#include <stdio.h>
#include <string.h>

typedef struct {
    char namaMapel[30];
    int kkm;
} Mapel;

typedef struct {
    char nama[30];
    char nis[30];
    char kelas[30];
    char sekolah[30];
} Identitas;

typedef struct {
    char predikat[30];
    float avg;
    int nilai;
    char status[30];
} Nilai;

void tampilMenu(Mapel m[]);
void inputIdentitas(Identitas id[]);
void inputNilai(Nilai n[], Mapel m[]);
void tampilRapor(Identitas *id, Nilai n[], Mapel m[]);
void simpanRapor(Identitas *id, Nilai n[], Mapel m[]);

int main() {
    Mapel mapel[5] = {
        {"WEB",76},
        {"Mobile",76},
        {"Basis Data",76},
        {"PBO",76},
        {"KEWIRAUSAHAAN",79}
    };

    Identitas siswa;
    Nilai nilai[5];

    tampilMenu(mapel);
    inputIdentitas(&siswa);
    inputNilai(nilai, mapel);
    tampilRapor(&siswa, nilai, mapel);
    simpanRapor(&siswa, nilai, mapel);
}

void tampilMenu(Mapel m[]) {
    printf("------------------------------\n");
    printf(" RAPOR SISWA SMKN 1 DENPASAR\n");
    printf("------------------------------\n");

    printf("| %-2s | %-15s | %-3s |\n", "NO", "NAMA", "KKM");
    printf("------------------------------\n");

    for(int i = 0; i < 5; i++ ) {
        printf("| %-2d | %-15s | %-3d |\n", i + 1, m[i].namaMapel, m[i].kkm);
    }
    printf("------------------------------\n");
}

void inputIdentitas(Identitas id[]) {
    printf("------------------------------\n");
    printf("    INPUT IDENTITAS SISWA\n");
    printf("------------------------------\n");

    printf("masukkan nama : ");
    scanf(" %[^\n]", id->nama);
    printf("masukkan nis : ");
    scanf(" %[^\n]", id->nis);
    printf("masukkan kelas : ");
    scanf(" %[^\n]", id->kelas);
    printf("masukkan asal sekolah : ");
    scanf(" %[^\n]", id->sekolah);
}

void inputNilai(Nilai n[], Mapel m[]) {
    printf("------------------------------\n");
    printf("      INPUT NILAI MAPEL\n");
    printf("------------------------------\n");

    for(int i = 0; i < 5; i++) {
        printf("masukkan nilai mapel %s : ", m[i].namaMapel);
        scanf("%d", &n[i].nilai);

        strcpy(n[i].status, (n[i].nilai >= m[i].kkm) ? "LULUS" : "TIDAK LULUS");
    }
}

void tampilRapor(Identitas *id, Nilai n[], Mapel m[]) {
    printf("------------------------------------------------------\n");
    printf("        RAPOR SISWA SMKN 1 DENPASAR\n");
    printf("------------------------------------------------------\n");

    printf("Nama    : %s\n", id->nama);
    printf("NIS     : %s\n", id->nis);
    printf("Kelas   : %s\n", id->kelas);
    printf("Sekolah : %s\n", id->sekolah);

    printf("------------------------------------------------------\n");
    printf("| %-2s | %-15s | %-3s | %-5s | %-13s |\n", "NO", "NAMA", "KKM", "NILAI", "STATUS");
    printf("------------------------------------------------------\n");

    float total = 0;

    for(int i = 0; i < 5; i++) {
        printf("| %-2d | %-15s | %-3d | %-5d | %-13s |\n",
               i + 1,
               m[i].namaMapel,
               m[i].kkm,
               n[i].nilai,
               n[i].status);

               total += n[i].nilai;
    }
    printf("------------------------------------------------------\n");

    n[0].avg = total / 5;

    if(n[0].avg >= 86 && n[0].avg < 100) {
        strcpy(n[0].predikat, "A");
    }
    else if(n[0].avg >= 85 && n[0].avg < 80 ) {
        strcpy(n[0].predikat, "B");
    }
    else if (n[0].avg >= 75 && n[0].avg < 79 ){
        strcpy(n[0].predikat, "C");
    }
    else {
        strcpy(n[0].predikat, "D");
    }

    printf("Rata Rata   : %.2f\n", n[0].avg);
    printf("Predikat    : %s\n", n[0].predikat);
    printf("------------------------------------------------------\n");

    char op;

    printf("Apakah data anda sudah benar?\n");
    printf("Tekan Y untuk cetak rapor\n");
    printf("Tekan N untuk input nilai ulang\n");

    printf("Pilihan Anda : ");
    scanf(" %c", &op);


    if(op == 'y' || op == 'Y') {
        simpanRapor(id, n, m);\
        printf("Rapor Berhasil Di Simpan");
    }
    else if(op == 'n' || op == 'N') {
        inputNilai(n, m);
        tampilRapor(id, n, m);
    }
}

void simpanRapor(Identitas *id, Nilai n[], Mapel m[]) {
    char fName[30];

    sprintf(fName, "Rapor_%s_%s.txt", id->nama, id->nis);

    FILE *fp = fopen(fName, "w");
    if(fp == NULL) {
        printf("File tidak bisa dibuat!");
        return;
    }

    fprintf(fp,"------------------------------------------------------\n");
    fprintf(fp,"        RAPOR SISWA SMKN 1 DENPASAR\n");
    fprintf(fp,"------------------------------------------------------\n");

    fprintf(fp,"Nama    : %s\n", id->nama);
    fprintf(fp,"NIS     : %s\n", id->nis);
    fprintf(fp,"Kelas   : %s\n", id->kelas);
    fprintf(fp,"Sekolah : %s\n", id->sekolah);

    fprintf(fp,"------------------------------------------------------\n");
    fprintf(fp,"| %-2s | %-15s | %-3s | %-5s | %-13s |\n", "NO", "NAMA", "KKM", "NILAI", "STATUS");
    fprintf(fp,"------------------------------------------------------\n");

    float total = 0;

    for(int i = 0; i < 5; i++) {
        fprintf(fp,"| %-2d | %-15s | %-3d | %-5d | %-13s |\n",
               i + 1,
               m[i].namaMapel,
               m[i].kkm,
               n[i].nilai,
               n[i].status);

               total += n[i].nilai;
    }

    fprintf(fp,"------------------------------------------------------\n");
    fprintf(fp,"Total Nilai : %.f\n", total );
    fprintf(fp,"Rata Rata   : %.2f\n", n[0].avg);
    fprintf(fp,"Predikat    : %s\n", n[0].predikat);
    fprintf(fp,"------------------------------------------------------\n");

    fclose(fp);
}
