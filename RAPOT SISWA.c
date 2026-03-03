#include <stdio.h>
#include <string.h>

typedef struct {
    char namaMapel[24];
    float kkm;
}Mapel;

typedef struct {
    char namaSiswa[128];
    char NIS[12];
    char Kelas[64];
    char Sekolah[128];
} Identitas;

typedef struct {
    char predikat[4];
    float avg;
    float nilai;
    char status[12];
} Nilai;

void tampilMenu(Mapel m[]);
void inputIdentitas(Identitas id[]);
void inputNilai(Nilai n[], Mapel m[]);
void tampilRapor(Identitas *id, Nilai n[], Mapel m[]);
void simpanRapor(Identitas *id, Nilai[], Mapel m[]);

int main(){
    Mapel mapel[5] = {
        {"WEB",75.0},
        {"DDPK", 75.0},
        {"MTK", 75.0},
        {"PJOK", 75.0},
        {"B.indo", 75.0}
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
    printf("====================================\n");
    printf("| %-2s | %-15s | %-2s |\n", "NO", "Mata Pelajaran", "KKM");
    printf("====================================\n");

    for (int i = 0; i < 5; i++) {
        printf("| %-2d | %-15s | %.2f |\n", i + 1, m[i].namaMapel, m[i].kkm);
    }
    printf("====================================\n");
}

void inputIdentitas(Identitas id[]) {
    printf("Masukkan nama: ");
    scanf(" %[^\n]", id->namaSiswa);
    printf("Masukkan NIS: ");
    scanf(" %[^\n]", id->NIS);
    printf("Masukkan Kelas: ");
    scanf(" %[^\n]", id->Kelas);
    printf("Masukkan asal sekolah: ");
    scanf(" %[^\n]", id->Sekolah);
}

void inputNilai(Nilai n[], Mapel m[]){
    for (int i = 0; i<5; i++) {
        printf("Masukkan nilai mapel %s: ", m[i].namaMapel );
        scanf("%f", &n[i].nilai);

        strcpy(n[i].status, (n[i].nilai >= m[i].kkm) ? "LULUS" : "TIDAK LULUS");
    }
}

void tampilRapor(Identitas *id, Nilai n[], Mapel m[]) {

    printf("============================================================\n");
    printf( "                          RAPOR SISWA                  \n");
    printf( "============================================================\n");
    printf("Nama : %s\n", id->namaSiswa);
    printf("NIS  : %s\n", id->NIS);
    printf( "------------------------------------------------------------\n");

    printf("| %-3s | %-18s | %-6s | %-6s | %-10s |\n",
           "No", "Mata Pelajaran", "KKM", "Nilai", "Status");
    printf( "------------------------------------------------------------\n");

    float total = 0;

    for (int i = 0; i < 5; i++) {
        printf("| %-3d | %-18s | %-6.2f | %-6.2f | %-10s |\n",
               i + 1,
               m[i].namaMapel,
               m[i].kkm,
               n[i].nilai,
               n[i].status);

        total += n[i].nilai;
    }

    printf("------------------------------------------------------------\n");

    // Hitung rata-rata
    n[0].avg = total / 5;

    // Tentukan predikat (logika diperbaiki)
    if (n[0].avg >= 80) {
        strcpy(n[0].predikat, "A");
    }
    else if (n[0].avg >= 65 && n[0].avg < 80) {
        strcpy(n[0].predikat, "B");
    }
    else {
        strcpy(n[0].predikat, "C");
    }

    printf("Rata-rata : %.2f\n", n[0].avg);
    printf("Predikat  : %s\n", n[0].predikat);
    printf("============================================================\n");

    char op;
    printf("Apakah data sudah benar? (y/n): ");
    scanf(" %c", &op);

    if (op == 'y' || op == 'Y') {
        simpanRapor(id, n, m);
        printf("Rapor berhasil disimpan!\n");
    }
    else if (op == 'n' || op == 'N') {
        inputNilai(n, m);
        tampilRapor(id, n, m);
    }
}

void simpanRapor(Identitas *id, Nilai n[], Mapel m[]) {
    char fName[64];

    sprintf(fName, "%s_%s.txt", id->namaSiswa, id->NIS);

    FILE *fp = fopen(fName, "w");
    if (fp == NULL) {
        printf("File tidak bisa dibuat!\n");
        return;
    }

    fprintf(fp, "============================================================\n");
    fprintf(fp, "                          RAPOR SISWA                  \n");
    fprintf(fp, "============================================================\n");
    fprintf(fp, "Nama : %s\n", id->namaSiswa);
    fprintf(fp, "NIS  : %s\n", id->NIS);
    fprintf(fp, "------------------------------------------------------------\n");

    fprintf(fp, "| %-3s | %-18s | %-6s | %-6s | %-10s |\n",
            "No", "Mata Pelajaran", "KKM", "Nilai", "Status");
    fprintf(fp, "------------------------------------------------------------\n");

    for (int i = 0; i < 5; i++) {
        fprintf(fp, "| %-3d | %-18s | %-6.2f | %-6.2f | %-10s |\n",
                i + 1,
                m[i].namaMapel,
                m[i].kkm,
                n[i].nilai,
                n[i].status);
    }

    fprintf(fp, "------------------------------------------------------------\n");
    fprintf(fp, "Rata-rata : %.2f\n", n[0].avg);
    fprintf(fp, "Predikat  : %s\n", n[0].predikat);
    fprintf(fp, "============================================================\n");

    fclose(fp);
}
