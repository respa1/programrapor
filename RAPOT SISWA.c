#include <stdio.h>
#include <string.h>

typedef struct {
    char namaMapel[30];
    int kkm;
} Mapel;

typedef struct {
    char namaSiswa[30];
    char nisn[30];
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
        {"Pemrograman Web",76},
        {"Pemrograman Mobile",76},
        {"Basis Data",76},
        {"PBO",76},
        {"Kewirausahaan",79},
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
    printf("========================================\n");
    printf("     DAFTAR MATA PELAJARAN DAN KKM\n");
    printf("========================================\n");
    printf("%-3s  %-20s %-3s\n", "No.", "Mata Pelajaran", "KKM");
    printf("----------------------------------------\n");

    for(int i = 0; i < 5; i++) {
        printf("%-3d  %-20s %-3d\n",
               i + 1,
               m[i].namaMapel,
               m[i].kkm);
    }
    printf("========================================\n");

}

void inputIdentitas(Identitas id[]) {
    printf("\n");
    printf("=== INPUT IDENTITAS SISWA ===\n");

    printf("%-15s : ","Nama Siswa");
    scanf(" %[^\n]", id->namaSiswa);
    printf("%-15s : ","NISN");
    scanf(" %[^\n]", id->nisn);
    printf("%-15s : ","Kelas");
    scanf(" %[^\n]", id->kelas);
    printf("%-15s : ","Nama Sekolah");
    scanf(" %[^\n]", id->sekolah);
}

void inputNilai(Nilai n[], Mapel m[]) {
    printf("\n");
    printf("=== INPUT NILAI MATA PELAJARAN ===\n");

    for(int i = 0; i < 5; i++) {
        printf("Nilai %-20s : ", m[i].namaMapel);
        scanf("%d", &n[i].nilai);

        strcpy(n[i].status, (n[i].nilai >= m[i].kkm) ? "LULUS" : "TIDAK LULUS");
    }
}

void tampilRapor(Identitas *id, Nilai n[], Mapel m[]) {
    printf("\n");
    printf("====================================================\n");
    printf("           RAPOR SMK NEGERI 1 DENPASAR\n");
    printf("====================================================\n");
    printf("%-15s : %s\n","Nama Siswa", id->namaSiswa);
    printf("%-15s : %s\n","NISN", id->nisn);
    printf("%-15s : %s\n","Kelas", id->kelas);
    printf("%-15s : %s\n","Sekolah", id->sekolah);
    printf("====================================================\n");
    printf("%-3s  %-20s %-6s %-6s %-13s\n", "No.", "Mata Pelajaran", "KKM", "Nilai", "Status");
    printf("----------------------------------------------------\n");

    float total = 0;

    for(int i = 0; i <5; i++) {
        printf("%-3d  %-20s %-6d %-6d %-13s\n",
               i + 1,
               m[i].namaMapel,
               m[i].kkm,
               n[i].nilai,
               n[i].status);

               total += n[i].nilai;
    }

    n[0].avg = total / 5;

    if(n[0].avg >= 86 && n[0].avg < 100) {
        strcpy(n[0].predikat, "A");
    }
    else if(n[0].avg >= 85 && n[0].avg < 80) {
        strcpy(n[0].predikat, "B");
    }
    else if(n[0].avg >= 79 && n[0].avg < 75) {
        strcpy(n[0].predikat, "C");
    }
    else {
        strcpy(n[0].predikat, "D");
    }

    printf("====================================================\n");
    printf("Rata-rata Nilai : %.2f\n", n[0].avg);
    printf("Predikat        : %s\n", n[0].predikat);
    printf("====================================================\n");

    char op;
    printf("\n");
    printf("Aapakah data anda sudah benar?\n");
    printf("Tekan Y untuk cetak rapor\n");
    printf("Tekan N untuk inpur ulang nilai\n");
    printf("Pilihan anda : ");
    scanf(" %c", &op);

    if(op == 'y' || op == 'Y') {
        simpanRapor(id, n, m);
        printf("Rapor Berhasil disimpan ke file 'rapor.txt\n");
        printf("\n");
        printf("Program Selesai. Terima Kasih!\n");
    }
    else if(op == 'n' || op == 'N') {
        printf("\n");
        printf("=== INPUT ULANG NILAI ===\n");
        inputNilai(n, m);
        tampilRapor(id, n, m);
    }


}

void simpanRapor(Identitas *id, Nilai n[], Mapel m[]) {
    char fName[30];

    sprintf(fName, "Rapor.txt");

    FILE *fp = fopen(fName, "w");
    if(fp == NULL) {
        printf("File tidak bisa dibuat!");
        return;
    }

    fprintf(fp,"\n");
    fprintf(fp,"====================================================\n");
    fprintf(fp,"           RAPOR SMK NEGERI 1 DENPASAR\n");
    fprintf(fp,"====================================================\n");
    fprintf(fp,"%-15s : %s\n","Nama Siswa", id->namaSiswa);
    fprintf(fp,"%-15s : %s\n","NISN", id->nisn);
    fprintf(fp,"%-15s : %s\n","Kelas", id->kelas);
    fprintf(fp,"%-15s : %s\n","Sekolah", id->sekolah);
    fprintf(fp,"====================================================\n");
    fprintf(fp,"%-3s  %-20s %-6s %-6s %-13s\n", "No.", "Mata Pelajaran", "KKM", "Nilai", "Status");
    fprintf(fp,"----------------------------------------------------\n");

    for(int i = 0; i <5; i++) {
        fprintf(fp,"%-3d  %-20s %-6d %-6d %-13s\n",
               i + 1,
               m[i].namaMapel,
               m[i].kkm,
               n[i].nilai,
               n[i].status);


    }

    fprintf(fp,"====================================================\n");
    fprintf(fp,"Rata-rata Nilai : %.2f\n", n[0].avg);
    fprintf(fp,"Predikat        : %s\n", n[0].predikat);
    fprintf(fp,"====================================================\n");
    fclose(fp);
}
