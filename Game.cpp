#include<iostream>
#include<cstring>
#include<vector>
#include<regex>
#include<cctype>
#include<algorithm>
#include<map>
#include<fstream>
#include <iomanip>
using namespace std;

class NguoiDung{
private:
    string hoTen,mk,email, gioiTinh, namSinh,sdt, cccd, maPin;
    double soDu=0;
    unsigned long long  maNguoiDung;
    vector<string> lichSuGiaoDich;
public:
    NguoiDung() {
    }
    string getemail(){
        return email;
    }
    void setemail(string email) {
        this->email = email;
    }
    int getmaNguoiDung(){
        return maNguoiDung;
    }
    double getSoDu (){
        return soDu;
    }
    string gethoTen(){
        return hoTen;
    }
    string getsodt(){
        return sdt;
    }
    string getmk(){
        return mk;
    }
    string getnamSinh(){
        return namSinh;
    }

    string getgioiTinh(){
        return gioiTinh;
    }
    string getcccd(){
        return cccd;
    }
    string getmaPin(){
        return maPin;
    }
    void setmaPin(string maPin){
        this->maPin=maPin;
    }
    void setmaNguoiDung(int maNguoiDung){
        this->maNguoiDung=maNguoiDung;
    }
    void setSoDu(double soDu){
        this->soDu=soDu;
    }
    void sethoTen(string hoTen){
        this->hoTen=hoTen;
    }
    void setsodt(string sodt){
        this->sdt=sodt;
    }
    void setmk(string mk){
        this->mk=mk;
    }
    void setnamSinh(string namSinh){
        this->namSinh=namSinh;
    }
    void setgioiTinh(string gioiTinh){
        this->gioiTinh=gioiTinh;
    }
    void setcccd(string cccd){
        if (isValidCCCD(cccd)) {
            this->cccd = cccd;
        } else {
            cout << "CCCD KHONG HOP LE!" << endl;
        }
    }
    void ghiLichSuGiaoDich(const string& noiDung){
        lichSuGiaoDich.push_back(noiDung);
    }
    bool truTien(double soTien) {
        if (soDu >= soTien) {
            soDu -= soTien;
            return true; // Trừ tiền thành công
        }
        return false; // Không đủ tiền
    }
    void CapNhatThongTin(string hoTenMoi,string sodtMoi){
        bool hopLe = true;
        for (char c : hoTenMoi) {
            if (!isalpha(c) && c != ' ') {
                hopLe = false;
                break;
            }
        }
        if (!hopLe) {
            cout << "TEN KHONG HOP LE! CHI DUOC CHUA CHU CAI VA DAU CACH.\n";

            return;
        }
        // Kiểm tra số điện thoại hợp lệ
        if (!isValidVietnamPhoneNumber(sodtMoi)) {
            cout << "SO DIEN THOAI KHONG HOP LE! VUI LONG NHAP LAI.\n";
            return;
        }
        // Gán giá trị khi hợp lệ
        hoTen = hoTenMoi;
        sdt = sodtMoi;
        cout << "CAP NHAT THONG TIN THANH CONG!" << endl;
        cout<<"HO TEN MOI: "<<hoTenMoi<<endl;
        cout<<"SO DIEN THOAI MOI: "<<sodtMoi<<endl;
    }
    void ThayDoiMatKhau(string mkMoi) {
        if (!isValidPassword(mkMoi)) {
            cout << "MAT KHAU KHONG HOP LE! PHAI CHUA IT NHAT MOT CHU CAI, MOT SO VA MOT KY TU DAC BIET.\n";
            return;
        }
        mk = mkMoi;
        cout << "CAP NHAT MAT KHAU THANH CONG!" <<endl;
        cout<<"MAT KHAU MOI: "<<mkMoi<<endl;
    }
    bool kiemTraMaPin() {
        string nhapPin;
        cout << "Nhap ma PIN de xac nhan giao dich: ";
        cin >> nhapPin;
        return nhapPin == maPin;
    }
    void napTien(double soTien, string ngayNap) {
        if (!kiemTraMaPin()) {
            cout << "LOI: MA PIN KHONG DUNG! GIAO DICH THAT BAI." << endl;
            return;
        }
        if (ngayNap.empty()) {
            cout << "LOI: Ngay nap tien khong hop le!" << endl;
            return;
        }
        soDu += soTien;
        lichSuGiaoDich.push_back(ngayNap + " | NAP TIEN (+) | " + to_string(soTien) + " VND");
        cout << "---------------------------------" << endl;
        cout << "NGAY GIAO DICH: " << ngayNap << endl;
        cout << "NAP " << soTien << " VND THANH CONG!" << endl;
        cout << "SO DU HIEN TAI: " << soDu << " VND" << endl;
        cout << "---------------------------------" << endl;
    }
    bool rutTien(double soTien, string ngayRut){
        if(!kiemTraMaPin()) {
            cout << "LOI: MA PIN KHONG DUNG! GIAO DICH THAT BAI." << endl;
            return false;
        }
        if(soTien>soDu){
            cout<<"RUT TIEN KHONG THANH CONG, SO DU CUA BAN KHONG DU!"<<endl;
            return 0;
        }
        else{
            soDu-=soTien;
            lichSuGiaoDich.push_back(ngayRut +"|RUT TIEN(-)|"+to_string(soTien)+"VND");
            cout<<"RUT "<<soTien<<"VND THANH CONG!"<<endl;
            return 1;
        }
    }
    void chuyenTien(string nguoinhan,double soTien, string ngayChuyen){
         cout<<"TEN NGUOI NHAN: ";
         cin.ignore();
         getline(cin,nguoinhan);
         cout<<"SO TIEN MUON CHUYEN: ";
         cin>>soTien;
         cin.ignore();
         cout<<"NGAY CHUYEN TIEN: ";
         getline(cin,ngayChuyen);
         if (!kiemTraMaPin()) {
             cout<<"CHUYEN TIEN KHONG THANH CONG!, MA PIN KHONG DUNG";
             return;
    }
        double phi = (soTien >= 10000000) ? soTien * 0.03 : 0;
        double tongTien = soTien + phi;
        if (tongTien > soDu) {
            cout << "CHUYEN TIEN KHONG THANH CONG, SO DU KHONG DU!" << endl;
            return;
        }
          soDu-=soTien;
         lichSuGiaoDich.push_back(ngayChuyen +"|CHUYEN TIEN(-)|" + to_string(soTien) + "VND DEN " + nguoinhan);
        if (phi > 0) {
            lichSuGiaoDich.push_back(ngayChuyen + "|THUE CHUYEN TIEN(-)|" + to_string(phi) + "VND");
        }
        lichSuGiaoDich.push_back(ngayChuyen + "|NHAN TIEN(+)|" + to_string(soTien) + "VND TU " + hoTen+" DEN "+nguoinhan);
        cout << "CHUYEN: " << soTien << "VND THANH CONG DEN" <<nguoinhan<< endl;
        if(phi>0){
         cout<<"DA TRU: "<<phi<<"VND TIEN THUE"<<endl;
    }
    }
    void xemLichSuGiaoDich(){
        cout << "====LICH SU GIAO DICH====\n";
        if (lichSuGiaoDich.empty()) {
            cout << "CHUA CO GIAO DICH NAO.\n";
            return;
        }
        for (string &gd : lichSuGiaoDich) {
            cout << gd << endl;
        }
    }
    // random số tk cho người dùng
    int taoRandom_maNguoiDung() {
        static bool seeded = false;
        if (!seeded) {
            srand(time(0));
            seeded = true;
        }
        int soTk = 1000000000 + rand() % 9000000000;
        return soTk;
    }
    // kiểm tra email
    bool isValidEmail(const string& email) {
        const regex pattern(R"(^[a-zA-Z0-9_.+-]+@[a-zA-Z0-9-]+\.[a-zA-Z0-9-.]+$)");
        return regex_match(email, pattern);
    }
    // kiem tra sdt
    bool isValidVietnamPhoneNumber(const string& phone) {
        const regex pattern(R"(^(\+84|0)(3[2-9]|5[2689]|7[0-9]|8[1-9]|9[0-9])[0-9]{7}$)");
        return regex_match(phone, pattern);
    }
    // kiểm tra mk
    bool isValidPassword(const string& password) {
        bool hasLetter = false, hasDigit = false, hasSpecialChar = false;
        for (char c : password) {
            if (isalpha(c)) hasLetter = true;
            else if (isdigit(c)) hasDigit = true;
            else hasSpecialChar = true;
        }
        return !password.empty() && hasLetter && hasDigit && hasSpecialChar;
    }
    // kiểm tra cccd
    bool isValidCCCD(const string& cccd) {
        const regex pattern(R"(^\d{12}$)");
        return regex_match(cccd, pattern);
    }
    void nhap(){
        // họ tên
        for(;;) {
            cout<<"NHAP TEN: ";
            cin.ignore();
            getline(cin,hoTen);
            bool hopLe = true;
            for (char c : hoTen) {
                if (!isalpha(c) && c != ' ') {
                    hopLe = false;
                    break;
                }
            }
            if (!hoTen.empty() && hopLe) {
                transform(hoTen.begin(), hoTen.end(), hoTen.begin(), ::toupper);
                sethoTen(hoTen); // Gọi setter thay vì gán trực tiếp
                cout << "NHAP HO TEN THANH CONG: " << gethoTen() << endl;// Dùng getter để hiển thị
                break; // Thoát vòng lặp khi nhập hợp lệ
            } else {
                cout << "TEN KHONG HOP LE, VUI LONG NHAP LAI.\n";
            }
        }
        cout<<endl;
        // so điện thoại
        cout<<"NHAP SO DIEN THOAI: ";
        getline(cin,sdt);
        while (!isValidVietnamPhoneNumber(sdt))
        {
            cout<<"SO DIEN THOAI KHONG HOP LE, VUI LONG NHAP LAI!: ";
            getline(cin,sdt);
        }
        setsodt(sdt);
        cout<<endl;
        //mật khẩu
        do {
            cout << "NHAP MAT KHAU: ";
            getline(cin,mk);
            if (!isValidPassword(mk)) {
                cout << "MAT KHAU KHONG HOP LE! PHAI CHUA IT NHAT MOT CHU CAI, MOT SO VA MOT KY TU DAC BIET. VUI LONG NHAP LAI.\n";
            }
        }
        while (!isValidPassword(mk));
        setmk(mk);
        cout << "MAT KHAU HOP LE!" << endl;
        // năm sinh
        time_t now = time(0);
        tm* ltm = localtime(&now);
        int namHienTai = 1900 + ltm->tm_year;
        do {
            cout << "NHAP NAM SINH (YYYY): ";
            getline(cin,namSinh);
            // Kiểm tra định dạng và điều kiện tuổi
            if (namSinh.length() == 4 && all_of(namSinh.begin(), namSinh.end(), ::isdigit)) {
                int namSinhInt = stoi(namSinh); // Chuyển từ string sang int
                if (namHienTai - namSinhInt >= 18) {
                    setnamSinh(namSinh);
                    cout << "NAM SINH HOP LE, BAN DA DU 18 TUOI !\n";
                    break;
                } else {
                    cout << "BAN CHUA DU DIEU KIEN DE!.\n";
                }
            } else {
                cout << "NAM SINH KHONG HOP LE !, VUI LONG NHAP LAI.\n";
            }
        } while (true);
        // giới tính
        int luaChon;
        do {
            cout << "CHON GIOI TINH:\n";
            cout << "1. NAM\n";
            cout << "2. NU\n";
            cout << "NHAP VAO LUA CHON!: ";
            cin >> luaChon;
            switch (luaChon) {
                case 1:
                    setgioiTinh("NAM");
                    break;
                case 2:
                    setgioiTinh("NU");
                    break;
                default:
                    cout << "LUA CHON KHONG HOP LE! VUI LONG NHAP LAI\n";
            }
        }
        while (luaChon != 1 && luaChon != 2);
        cout << "BAN DA CHON GIOI TINH: " << getgioiTinh()<< endl;
        // mã người dùng
        maNguoiDung = taoRandom_maNguoiDung();
        setmaNguoiDung(taoRandom_maNguoiDung());
        cout << "MA NGUOI DUNG: " << getmaNguoiDung()<< endl;
        cout<<endl;
        // email
        cin.ignore();
        do{
            cout<<"NHAP EMAIL:";
            getline(cin,email);
            if (!isValidEmail(email)) {
                cout << "EMAIL KHONG HOP LE VUI LONG NHAP LAI! \n";
            }
        } while(!isValidEmail(email));
        setemail(email);
        cout<<endl;
        //cccd
        do {
            cout << "NHAP SO CCCD(12 SO): ";
            getline(cin, cccd);
            setcccd(cccd);
            if (!isValidCCCD(cccd)) {
                cout << "CCCD KHONG HOP LE VUI LONG NHAP LAI.\n";
            }
        } while (!isValidCCCD(cccd));
        //ma pin
        do {
            cout << "NHAP MA PIN (4 SO): ";
            string maPinStr;
            cin >> maPinStr;

            if (maPinStr.length() == 4 && all_of(maPinStr.begin(), maPinStr.end(), ::isdigit)) {
                setmaPin(maPinStr);// Chuyển chuỗi thành số nguyên sau khi kiểm tra hợp lệ
                break;
            }
            cout << "MA PIN KHONG HOP LE! VUI LONG NHAP LAI.\n";
        } while (true);

        cout << "MA PIN HOP LE: " << getmaPin() << endl;
    }
    void in() {
        cout << "HO TEN: " << gethoTen() << endl;
        cout << "SO DIEN THOAI: " << getsodt() << endl;
        cout << "MAT KHAU: " << getmk() << endl;
        cout << "NAM SINH: " << getnamSinh() << endl;
        cout << "GIOI TINH: " << getgioiTinh() << endl;
        cout << "MA NGUOI DUNG: " << getmaNguoiDung() << endl;
        cout << "SO DU: " << getSoDu() << endl;
        cout << "EMAIL: " << getemail() << endl; 
        cout << "CCCD: " << getcccd() << endl;
        cout << "MA PIN: " << getmaPin() << endl;
    }
    void in(ofstream& file) {
        file << "HO TEN: " << gethoTen() << endl;
        file << "SO DIEN THOAI: " << getsodt() << endl;
        file << "MAT KHAU: " << getmk() << endl;
        file << "NAM SINH: " << getnamSinh() << endl;
        file << "GIOI TINH: " << getgioiTinh() << endl;
        file << "MA NGUOI DUNG: " << getmaNguoiDung() << endl;
        file << "SO DU: " << getSoDu() << endl;
        file << "EMAIL: " << getemail() << endl;
        file << "CCCD: " << getcccd() << endl;
        file << "MA PIN: " << getmaPin() << endl;
    }
    void luuLichSuVaoFile(ofstream& file) {
        file << "==== LICH SU GIAO DICH ====\n";
        for (const string& gd : lichSuGiaoDich)
            file << gd << endl;
        file << "===========================\n";
    }
};
class TrainTicketSystem {
private:
    map<string, int> prices;
    NguoiDung* nguoidung;
    string startLocation, endLocation;
    int numberOfTickets, totalPrice;
public:
    TrainTicketSystem(NguoiDung* user) {
        nguoidung = user;
        prices["HaNoiSaiGon"] = 500000;
        prices["HaNoiDaNang"] = 350000;
        prices["HaNoiHaiPhong"] = 150000;
        prices["SaiGonDaNang"] = 400000;
        prices["SaiGonHaiPhong"] = 450000;
        prices["DaNangHaiPhong"] = 200000;
    }
    void displayTicketPrice(string startLocation, string endLocation) {
        string route = startLocation + endLocation;
        if (prices.find(route) != prices.end()) {
            cout << "Gia ve tu " << startLocation << " den " << endLocation << " la: "
                 << prices[route] << " dong." << endl;
        } else {
            cout << "Khong co tuyen tau tu " << startLocation << " den " << endLocation << " trong he thong.\n";
        }
    }

    void processTicketPurchase() {
        cout << "Nhap ga xuat phat (vi du: HaNoi, SaiGon, DaNang, HaiPhong): ";
        cin >> startLocation;
        cout << "Nhap ga den (vi du: HaNoi, SaiGon, DaNang, HaiPhong): ";
        cin >> endLocation;

        string route = startLocation + endLocation;
        if (prices.find(route) == prices.end()) {
            cout << "Khong co tuyen tau tu " << startLocation << " den " << endLocation << " trong he thong.\n";
            return;
        }

        displayTicketPrice(startLocation, endLocation);
        cout << "Nhap so ve ban muon mua: ";
        cin >> numberOfTickets;

       totalPrice = prices[route] * numberOfTickets;

        // Kiểm tra số dư
        if (nguoidung->getSoDu() < totalPrice) {
            cout << "LOI: SO DU KHONG DU DE MUA VE!\n";
            return;
        }

        // Xác nhận mã PIN trước khi thanh toán
        if (!nguoidung->kiemTraMaPin()) {
            cout << "LOI: MA PIN KHONG DUNG! GIAO DICH THAT BAI.\n";
            return;
        }
        // Trừ tiền từ tài khoản
        nguoidung->setSoDu(nguoidung->getSoDu() - totalPrice);
        nguoidung->ghiLichSuGiaoDich("MUA VE TAU: " + to_string(numberOfTickets) + " VE TU " + startLocation + " DEN " + endLocation + " - " + to_string(totalPrice) + " VND");
        cout << "---------------------------------" << endl;
        cout << "MUA VE THANH CONG!\n";
        cout << "TUYEN: " << startLocation << " -> " << endLocation << endl;
        cout << "SO VE: " << numberOfTickets << endl;
        cout << "TONG GIA: " << totalPrice << " VND" << endl;
        cout << "SO DU CON LAI: " << nguoidung->getSoDu() << " VND" << endl;
        cout << "---------------------------------" << endl;
    }
    void luuThongTintau(ofstream& file) {
        file << "TUYEN: " << startLocation << " -> " << endLocation << endl;
        file << "SO VE: " << numberOfTickets << endl;
        file << "TONG GIA: " << totalPrice << " VND" << endl;
        file << "---------------------------------" << endl;
    }

};
class BusTicketSystem
{
    private:
        map<string, int> prices;
        NguoiDung *nguoidung;
        string startLocation, endLocation;
        int numberOfTickets, totalPrice;
    public:
    BusTicketSystem(NguoiDung* user) {
        nguoidung = user;
        prices["HaNoiSaiGon"] = 600000;
        prices["HaNoiDaNang"] = 400000;
        prices["HaNoiHaiPhong"] = 120000;
        prices["SaiGonDaNang"] = 450000;
        prices["SaiGonHaiPhong"] = 500000;
        prices["DaNangHaiPhong"] = 250000;
    }
       void displayTicketPrice(string startLocation, string endLocation) {
        string route = startLocation + endLocation;
        if (prices.find(route) != prices.end()) {
            cout << "Gia ve xe tu " << startLocation << " den " << endLocation << " la: "
                 << prices[route] << " dong." << endl;
        } else {
            cout << "Khong co tuyen xe tu " << startLocation << " den " << endLocation << " trong he thong.\n";
        }
    }
    void processTicketPurchase() {


        cout << "Nhap ben xe xuat phat (vi du: HaNoi, SaiGon, DaNang, HaiPhong): ";
        cin >> startLocation;
        cout << "Nhap ben xe den (vi du: HaNoi, SaiGon, DaNang, HaiPhong): ";
        cin >> endLocation;

        string route = startLocation + endLocation;
        if (prices.find(route) == prices.end()) {
            cout << "Khong co tuyen xe tu " << startLocation << " den " << endLocation << " trong he thong.\n";
            return;
        }

        displayTicketPrice(startLocation, endLocation);
        cout << "Nhap so ve ban muon mua: ";
        cin >> numberOfTickets;

        totalPrice = prices[route] * numberOfTickets;

        // Kiểm tra số dư
        if (nguoidung->getSoDu() < totalPrice) {
            cout << "LOI: SO DU KHONG DU DE MUA VE!\n";
            return;
        }

        // Xác nhận mã PIN trước khi thanh toán
        if (!nguoidung->kiemTraMaPin()) {
            cout << "LOI: MA PIN KHONG DUNG! GIAO DICH THAT BAI.\n";
            return;
        }

        // Trừ tiền từ tài khoản
        nguoidung->setSoDu(nguoidung->getSoDu() - totalPrice);
        nguoidung->ghiLichSuGiaoDich("MUA VE XE: " + to_string(numberOfTickets) + " VE TU " + startLocation + " DEN " + endLocation + " - " + to_string(totalPrice) + " VND");
        cout << "---------------------------------" << endl;
        cout << "MUA VE XE THANH CONG!\n";
        cout << "TUYEN: " << startLocation << " -> " << endLocation << endl;
        cout << "SO VE: " << numberOfTickets << endl;
        cout << "TONG GIA: " << totalPrice << " VND" << endl;
        cout << "SO DU CON LAI: " << nguoidung->getSoDu() << " VND" << endl;
        cout << "---------------------------------" << endl;
    }
    void luuThongTinVeXe(ofstream& file) {
        file << "====THONG TIN MUA VE XE====\n";
        file << "TUYEN: " << startLocation << " -> " << endLocation << endl;
        file << "SO VE: " << numberOfTickets << endl;
        file << "TONG GIA: " << totalPrice << " VND" << endl;
        file << "---------------------------------\n";
    }

};
class AirlineTickets{
    private:
    struct Flight {
        string flightNumber;
        string khoihanh,dichden,date,time;
        double price;
    };

    struct Ticket {
        string hoTen;
        Flight flight;
        bool isPaid;
    };
    vector<Flight> availableFlights;
    vector<Ticket> bookedTickets;
    NguoiDung *nguoidung;
    Flight generateFlightDetails(string from, string to, int index) {
        time_t now = time(0);
        tm *ltm = localtime(&now);
        int randomDays = rand() % 7 + 1;
        ltm->tm_mday += randomDays;
        mktime(ltm);
        char dateStr[11];
        strftime(dateStr, sizeof(dateStr), "%Y-%m-%d", ltm);
        string times[] = {"06:00", "09:15", "12:30", "15:45", "18:00", "21:30"};
        string randomTime = times[rand() % 6];
        double randomPrice = 1200000 + (rand() % 900000);
        string flightNumber = "VN" + to_string(100 + index);
        return {flightNumber, from, to, dateStr, randomTime, randomPrice};
    }
    public:
    AirlineTickets(NguoiDung* user) {
        nguoidung = user;
    }
    void searchFlights(string from, string to) {
        availableFlights.clear();
        int numFlights = rand() % 3 + 2; // Sinh từ 2 đến 4 chuyến bay

        for (int i = 0; i < numFlights; i++) {
            availableFlights.push_back(generateFlightDetails(from, to, i));
        }

        cout << "CAC CHUYEN BAY CO SAN TU " << from << " DEN " << to << ":\n";
        cout << left << setw(10) << "MA CHUYEN" << "|"
             << setw(12) << "DIEM DI" << "|"
             << setw(12) << "DIEM DEN" << "|"
             << setw(8) << "GIO BAY" << "|"
             << setw(12) << "GIA VE" << endl;
        cout << "-------------------------------------------------------------\n";

        for (const auto& flight : availableFlights) {
            cout << left << setw(10) << flight.flightNumber << "|"
                 << setw(12) << flight.khoihanh << "|"
                 << setw(12) << flight.dichden << "|"
                 << setw(8) << flight.time << "|"
                 << setw(12) << fixed << setprecision(0) << flight.price << " VND" << endl;
        }
    }

    void bookTicket(string passenger, string flightNumber) {
        bool found = false;
        for (const auto& flight : availableFlights) {
            if (flight.flightNumber == flightNumber) {
                double ticketPrice = flight.price;

                // Kiểm tra số dư
                if (nguoidung->getSoDu() < ticketPrice) {
                    cout << "LOI: SỐ DU KHONG DU DE DAT VE!\n";
                    return;
                }

                // Xác nhận mã PIN trước khi thanh toán
                if (!nguoidung->kiemTraMaPin()) {
                    cout << "LOI: MA PIN KHONG DUNG! GIAO DICH THAT BAI.\n";
                    return;
                }
                // Trừ tiền từ tài khoản
                nguoidung->setSoDu(nguoidung->getSoDu() - ticketPrice);

                bookedTickets.push_back({passenger, flight, true});
                nguoidung->ghiLichSuGiaoDich("MUA VE MAY BAY: " + flightNumber + " TU " + flight.khoihanh + " DEN " + flight.dichden + " - " + to_string(ticketPrice) + " VND");
                cout << "---------------------------------" << endl;
                cout << "DAT VE THANH CONG!\n";
                cout << "HANH KHACH: " << passenger << endl;
                cout << "MA CHUYEN BAY: " << flightNumber << endl;
                cout << "NGAY BAY: " << flight.date << " - " << flight.time << endl;
                cout << "GIA VE: " << ticketPrice << " VND" << endl;
                cout << "SO DU CON LAI: " << nguoidung->getSoDu() << " VND" << endl;
                cout << "---------------------------------" << endl;

                found = true;
                break;
            }
        }
        if (!found) {
            cout << "MA CHUYEN BAY KHONG HOP LE!\n";
        }
    }
    void luuThongTinVeMayBay(ofstream& file) {
        for (const auto& ticket : bookedTickets) {
            file << "==== THONG TIN MUA VE MAY BAY ====\n";
            file << "HANH KHACH: " << ticket.hoTen << endl;
            file << "TUYEN: " << ticket.flight.khoihanh << " -> " << ticket.flight.dichden << endl;
            file << "MA CHUYEN BAY: " << ticket.flight.flightNumber << endl;
            file << "NGAY BAY: " << ticket.flight.date << " - " << ticket.flight.time << endl;
            file << "GIA VE: " << fixed << setprecision(0) << ticket.flight.price << " VND\n";
            file << "----------------------------------\n";
        }
    }
};
void hienThiMenu() {
    int luaChon = -1;
    NguoiDung nguoidung;
    string nguoinhan;
    TrainTicketSystem trainSystem(&nguoidung);
    BusTicketSystem busSystem(&nguoidung);
    AirlineTickets airlineSystem(&nguoidung);
    double soTien;
    string ngayRut,ngayNap,HoTenMoi,SoDtMoi,mkMoi,ngayChuyen,from, to, passenger, flightNumber;

    while (luaChon != 0) {
        cout<<"  ||============================= MENU =======================================|| \n";
        cout<<"  ||                    UNG DUNG GIAO DICH - DICHUYEN247                      ||   \n";
        cout<<"  ||==========================================================================||\n";
        cout <<"  ||01. DANG KI TAI KHOAN.                                                    ||" << endl;
        cout <<"  ||02. THONG TIN NGUOI DUNG.                                                 ||" << endl;
        cout <<"  ||03. NAP TIEN.                                                             ||" << endl;
        cout <<"  ||04. RUT TIEN.                                                             ||" << endl;
        cout <<"  ||05. CHUYEN TIEN.                                                          ||" << endl;
        cout <<"  ||06. XEM SO DU.                                                            ||" << endl;
        cout <<"  ||07. XEM LICH SU GIAO DICH.                                                ||" << endl;
        cout <<"  ||08. CAP NHAT THONG TIN.                                                   ||" << endl;
        cout <<"  ||09. DOI MAT KHAU.                                                         ||" << endl;
        cout <<"  ||10. MUA VE XE.                                                            ||" << endl;
        cout <<"  ||11. MUA VE TAU.                                                           ||" << endl;
        cout <<"  ||12. MUA VE MAY BAY.                                                       ||" << endl;
        cout <<"  ||13.LICH SU HOAT DONG.                                                     ||"<< endl;
        cout <<"  ||0. THOAT.                                                                 ||" << endl;
        cout <<"  ||==========================================================================||" << endl;
        cout << "NHAP LUA CHON: ";
        cin >> luaChon;
        if (luaChon == -1) {
            cout << "LUA CHON KHONG HOP LE!VUI LONG NHAP LAI." << endl;
            continue;
        }
        switch (luaChon) {
            case 1: {

                ofstream logFile("hoat_dong.txt", ios::app);
                cout<<"====XIN MOI NHAP THONG TIN THEO YEU CAU====\n";

                nguoidung.nhap();

                cout<<"====THONG TIN DUOC CAP NHAT====\n";
                nguoidung.in();
                cout<<"====CHUC MUNG QUY KHACH DA DANG KY TAI KHOAN THANH CONG====\n";
                logFile<< "====THONG TIN DUOC CAP NHAT====\n";
                nguoidung.in(logFile);
                logFile<< "====CHUC MUNG BAN DA DANG KY THANH CONG====\n";
                logFile.close();
                break;
            }
            case 2: {
                ofstream logFile("hoat_dong.txt", ios::app);
                cout<<"====THONG TIN CUA BAN====\n";

                nguoidung.in();

                cout<<"==========================\n";
                logFile << "THONG TIN NGUOI DUNG:\n";
                nguoidung.in(logFile);
                logFile.close();
                break;
            }
            case 3: {
                ofstream logFile("hoat_dong.txt", ios::app);
                cout<<"====NAP TIEN====\n";
                cout << "Nhap so tien muon nap: ";
                cin >> soTien;
                cin.ignore();
                cout << "Nhap ngay giao dich (dd/mm/yyyy): ";
                getline(cin, ngayNap);
                nguoidung.napTien(soTien, ngayNap);
                cout << "ngayNap " << ngayNap << endl;
                cout<<"===================\n";
                logFile << "====NAP TIEN====\n";
                logFile << "So tien: " << soTien << endl;
                logFile << "Ngay giao dich: " << ngayNap << endl;
                logFile<< "============================\n";
                logFile.close();
                break;
            }
            case 4:{
                ofstream logFile("hoat_dong.txt", ios::app);
                cout<<"====RUT TIEN====\n";
                cout<<"SO TIEN MUON RUT: ";
                cin >> soTien;
                cin.ignore();
                cout<<"NGAY RUT TIEN: ";
                cin >> ngayRut;
                nguoidung.rutTien(soTien, ngayRut);
                cout<<"===================\n";
                logFile << "====RUT TIEN====\n";
                logFile << "So tien: " << soTien << endl;
                logFile << "Ngay rut: " << ngayRut << endl;
                logFile<< "============================\n";
                logFile.close();
                break;
             }
                case 5: {
                    ofstream logFile("hoat_dong.txt", ios::app);
                    cout<<"====CHUYEN TIEN====\n";

                    nguoidung.chuyenTien(nguoinhan,soTien,ngayChuyen);
                    logFile << "====CHUYEN TIEN====\n";
                    logFile << "TEN NGUOI NHAN: " << nguoinhan << endl;
                    logFile << "Ngay chuyen: " << ngayChuyen << endl;
                    logFile<<  "SO TIEN: " << soTien << endl;
                    logFile<< "============================\n";
                    logFile.close();
                    break;
                 }
                case 6: {
                    ofstream logFile("hoat_dong.txt", ios::app);
                    cout << "SO DU HIEN TAI: " << nguoidung.getSoDu() << " VND" << endl;
                    cout<<"======================\n";
                    logFile << "====SO DU HIEN TAI====\n";
                    logFile << "SO DU HIEN TAI: " << nguoidung.getSoDu() << " VND" << endl;
                    logFile<< "============================\n";
                    logFile.close();
                    break;
                }
                case 7: {
                    ofstream logFile("hoat_dong.txt", ios::app);
                    nguoidung.xemLichSuGiaoDich();
                    cout<<"======================\n";
                    nguoidung.luuLichSuVaoFile(logFile);
                    logFile<< "============================\n";
                    logFile.close();
                    break;
                }
                case 8: {
                    ofstream logFile("hoat_dong.txt", ios::app);
                    cout<<"====CAP NHAT THONG TIN====\n";
                    cout<<"NHAP TEN MOI: ";
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    getline(cin, HoTenMoi);
                    cout<<"NHAP SO DIEN THOAI MOI: ";
                    getline(cin, SoDtMoi);
                    nguoidung.CapNhatThongTin(HoTenMoi, SoDtMoi);
                    cout<<"============================\n";
                    logFile << "====CAP NHAT THONG TIN====\n";
                    logFile << "SO DIEN THOAI MOI: "<<SoDtMoi<<endl;
                    logFile<< "HO TEN MOI: "<<HoTenMoi<<endl;
                    logFile<< "=============================\n";
                    logFile.close();
                    break;
            }
                    case 9: {
                        ofstream logFile("hoat_dong.txt", ios::app);
                        cout<<"====CAP NHAT MAT KHAU====\n";
                        cout<<"NHAP MAT KHAU MOI: ";
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        getline(cin, mkMoi);
                        nguoidung.ThayDoiMatKhau(mkMoi);
                        cout<<"==========================\n";
                        logFile << "====CAP NHAT MAT KHAU====\n";
                        logFile<<"THAY DOI MAT KHAU: "<<mkMoi<<endl;
                        logFile<<"===========================\n";
                        logFile.close();
                        break;
            }

                case 10: {
                    ofstream logFile("hoat_dong.txt", ios::app);
                    cout << "====MUA VE TAU====\n";
                    trainSystem.processTicketPurchase(); // đúng object trainSystem nha
                    cout << "====================\n";
                    logFile << "====MUA VE TAU====\n";
                    trainSystem.luuThongTintau(logFile); // gọi đúng object đã dùng mua vé
                    logFile.close(); // nhớ đóng file
                    logFile<< "==========================\n";
                    break;
            }
                case 11: {
                ofstream logFile("hoat_dong.txt", ios::app);
                cout<<"====MUA VE TAU====\n";
                trainSystem.processTicketPurchase();
                cout<<"=======================\n";
                logFile<<"====MUA VE XE====\n";
                trainSystem.luuThongTintau(logFile);
                logFile.close();
                logFile<< "=========================\n";
                break;
            }
                case 12: {
                    ofstream logFile("hoat_dong.txt", ios::app);
                    cout<<"====MUA VE MAY BAY====\n";
                    cout << "NHAP DIEM XUAT PHAT: ";
                    cin >> from;
                    cout << "NHAP DIEM DEN: ";
                    cin >> to;
                    airlineSystem.searchFlights(from, to);
                    cout << "NHAP MA CHUYEN BAY MUON DAT: ";
                    cin >> flightNumber;
                    cout << "NHAP HO TEN HANH KHACH: ";
                    cin.ignore();
                    getline(cin, passenger);
                    airlineSystem.bookTicket(passenger, flightNumber);
                    cout<<"==========================\n";
                    logFile<<"----MUA VE MAY BAY----\n";
                    airlineSystem.luuThongTinVeMayBay(logFile);
                    logFile.close();
                    logFile<<"-----------------------\n";
                    break;
                }
                case 13: {
                    system("notepad hoat_dong.txt");
                    break;
                }
                case 0:
                     cout << "DANG XUAT." << endl;
                break;
                default:

                    cout << "LUA CHON KHONG HOP LE !, VUI LONG NHAP LAI." << endl;

            }
        }
    }

    int main() {
        hienThiMenu();

    }



