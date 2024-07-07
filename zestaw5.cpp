#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <memory>

class Canvas{

    protected:
        int width;
        int height;

    public:

        Canvas(){
            width = 0;
            height = 0;
        }

        Canvas(int w, int h){
            width = w;
            height = h;
        }

        virtual void Draw(int x, int y, char c) = 0;
        virtual void Show() = 0;
        virtual void Save(const std::string file) = 0;

        int getW(){
            return width;
        }

        int getH(){
            return height;
        }

        virtual ~Canvas(){};

};

class ASCIICanvas : public Canvas{
    private:
        std::vector<std::vector<char>> piksel;

    public:
        ASCIICanvas(int w, int h) : Canvas(w, h){
            piksel = std::vector<std::vector<char>>(h, std::vector<char>(w, ' '));
        }

        void Draw(int x, int y, char c) override {
            if(x >= 0 && x < width && y >= 0 && y < height){
                piksel[y][x] = c;
            }
        }

        void Show() override {
            std::cout << "+";
            for (int i = 0; i < width; ++i) {
                std::cout << "-";
            }
            std::cout << "+\n";

            for(auto i : piksel){
                std::cout << "|";
                for(auto j : i){
                    std::cout << j;
                }
                std::cout << "|\n";
            }

            std::cout << "+";
            for (int i = 0; i < width; ++i) {
                std::cout << "=";
            }
            std::cout << "+\n";
        }

        void Save(const std::string file) override {
            std::ofstream f(file);
            f << "+";
                for (int i = 0; i < width; ++i) {
                f << "-";
            }
            f << "+\n";

            for(auto i : piksel){
                f << "|";
                for(auto j : i){
                    f << j;
                }
                f << "|\n";
            }
            f << "+";
            for (int i = 0; i < width; ++i) {
                f << "-";
            }
            f << "+\n";

        }

        void DrawShadow(int x, int y, char s){
            if(x >= 0 && x < width && y >= 0 && y < height && piksel[y][x] == ' '){
                piksel[y][x] = s;
            }
        }

        ~ASCIICanvas(){}
};

class Figure{

    protected:
        int center_x = 0;
        int center_y = 0;

    public:
        Figure(int x, int y){
            center_x = x;
            center_y = y;
        } 

        virtual ~Figure(){}

        virtual void Draw(Canvas &c, char s){}
        virtual void Shadow(ASCIICanvas &canvas, int xl, int yl, char s) = 0;
};

class Rectangle : public Figure{

    protected:
        int width;
        int height;

    public:

        Rectangle(int x, int y, int w, int h) : Figure(x, y){
            width = w;
            height = h;
        }

        ~Rectangle(){}

        void Draw(Canvas &c, char s) override {
            int x = center_x - width / 2;
            int y = center_y - height / 2;
    
            for(int i = y; i < y + height; i++){
                for(int j = x; j < x + width; j++){
                    c.Draw(j, i, s);
                }
            }
        }

        void Shadow(ASCIICanvas &canvas, int xl, int yl, char s) override {
            int xg = center_x - width / 2;
            int yg = center_y - height / 2;

            int xd = center_x + width / 2;
            int yd = center_y + height / 2;

            if(yg == yl){
                if(xg > xl){            
                    for(int i = xg; i <= canvas.getW(); i++){
                        for(int j = yg; j <= yd; j++){
                            canvas.DrawShadow(i, j, s);
                        } 
                    }
                    for(int i = 0; i < canvas.getW() - xg; i++){
                        for(int j = 0; j < i; j++){
                            canvas.DrawShadow(xd + i, yd + j, s);
                        }
                    }
                }else{
                    for(int i = xg; i >= 0; i--){
                        for(int j = yg; j <= yd; j++){
                            canvas.DrawShadow(i, j, s);
                        } 
                    }
                    for(int i = xg; i > 0; i--){
                        for(int j = 0; j < i; j++){
                            canvas.DrawShadow(xg - i, yd + j, s);
                        }
                    }
                }
            }else if(yd == yl){
                if(xg > xl){
                    for(int i = xg; i <= canvas.getW(); i++){
                        for(int j = yg; j <= yd; j++){
                            canvas.DrawShadow(i, j, s);
                        } 
                    }
                    for(int i = 0; i < canvas.getW() - xg; i++){
                        for(int j = 0; j < i; j++){
                            canvas.DrawShadow(xg + i, yg - j, s);
                        }
                    }
                }else{
                    for(int i = xg; i >= 0; i--){
                        for(int j = yg; j <= yd; j++){
                            canvas.DrawShadow(i, j, s);
                        } 
                    }
                    for(int i = xd; i >= 0; i--){
                        for(int j = 0; j < i; j++){
                            canvas.DrawShadow(xd - i, yg - j, s);
                        }
                    }
                }
            }else if((yg < yl) && (yd > yl)){
                if(xg > xl){
                    for(int i = xg; i <= canvas.getW(); i++){
                        for(int j = yg; j <= yd; j++){
                            canvas.DrawShadow(i, j, s);
                        } 
                    }
                    for(int i = 0; i < canvas.getW() - xg; i++){
                        for(int j = 0; j < i; j++){
                            canvas.DrawShadow(xg + i, yd + j, s);
                        }
                    }
                    for(int i = 0; i < canvas.getW() - xg; i++){
                        for(int j = 0; j < i; j++){
                            canvas.DrawShadow(xg + i, yg - j, s);
                        }
                    }
                }else{
                    for(int i = xg; i >= 0; i--){
                        for(int j = yg; j <= yd; j++){
                            canvas.DrawShadow(i, j, s);
                        } 
                    }
                    for(int i = xd; i > 0; i--){
                        for(int j = 0; j < i; j++){
                            canvas.DrawShadow(xd - i, yd + j, s);
                        }
                    }
                    for(int i = xd; i >= 0; i--){
                        for(int j = 0; j < i; j++){
                            canvas.DrawShadow(xd - i, yg - j, s);
                        }
                    }
                }

            }else if(yg > yl){
                if(xg > xl){
                    for(int i = 0; i <= canvas.getW() - xd; i++){
                        for(int j = 0; j < yg; j++){
                            canvas.DrawShadow(xd + i, yg + j + i, s);
                        }
                    }
                }else{
                    for(int i = 0; i <= xg; i++){
                        for(int j = 0; j < yg; j++){
                            canvas.DrawShadow(xd - i - j, yg + j, s);
                        }
                    }
                }
            }else if(yd < yl){
                if(xg > xl){
                   for(int i = 0; i <= canvas.getW() - xd; i++){
                        for(int j = 0; j < yd; j++){
                            canvas.DrawShadow(xd + i, yd - j - i, s);
                        }
                    }
                }else if(xg == xl){
                    for(int i = xg; i < xd; i++){
                        for(int j = 0; j < yd; j++){
                            canvas.DrawShadow(i, j, s);
                        }
                    }                   
                }else if(xd == xl){
                    for(int i = xg; i < xd; i++){
                        for(int j = 0; j < yd; j++){
                            canvas.DrawShadow(i, j, s);
                        }
                    }
                }else{
                    for(int i = xg; i >= 0; i--){
                        for(int j = yg; j < yd; j++){
                            canvas.DrawShadow(i, j, s);
                        } 
                    }
                    for(int i = xd; i >= 0; i--){
                        for(int j = 0; j < i; j++){
                            canvas.DrawShadow(xd - i, yg - j, s);
                        }
                    }
                }
            }
        }   
};

class Square : public Rectangle{
    public:
        Square(int x, int y, int w) : Rectangle(x, y, w, w){}
        ~Square(){}

};

class Circle : public Figure{
    private:
        int radius;

    public:
        Circle(int x, int y, int r) : Figure(x, y){
            radius = r;
        }
        ~Circle(){}

        void Draw(Canvas &c, char s) override {
            for(int y = -radius; y <= radius; y++){
                for(int x = -radius; x <= radius; x++){
                    if(x*x + y*y <= radius*radius){
                        c.Draw(center_x + x, center_y + y, s);
                    }
                }
            }

        }

        void Shadow(ASCIICanvas &canvas, int xl, int yl, char s) override{

            if(yl < (center_y - radius)){
                if(center_x > xl){
                   for(int i = 0; i <= canvas.getW() - center_x; i++){
                        for(int j = 0; j < center_y; j++){
                            canvas.DrawShadow(center_x + i, center_y - radius + j + i, s);
                        }
                    }
                    for(int i = 0; i <= canvas.getW() - center_x; i++){
                        for(int j = center_y - radius; j < center_y + radius; j++){
                            canvas.DrawShadow(center_x + i, j, s);
                        }
                    }
                }else{
                   for(int i = 0; i <= center_x; i++){
                        for(int j = 0; j < center_y + radius; j++){
                            canvas.DrawShadow(center_x - i, center_y - radius + j, s);
                        }
                    }
                    for(int i = 0; i <= center_x - radius; i++){
                        for(int j = 0; j < center_y + radius; j++){
                            canvas.DrawShadow(center_x - i, center_y + radius + j, s);
                        }
                    }
                }

            }else if(yl > (center_y + radius)){
                if(center_x > xl){
                   for(int i = 0; i <= canvas.getW() - center_x; i++){
                        for(int j = 0; j < center_y; j++){
                            canvas.DrawShadow(center_x + i, center_y - radius - j, s);
                        }
                    }
                    for(int i = 0; i <= canvas.getW() - center_x; i++){
                        for(int j = center_y - radius; j < center_y + radius; j++){
                            canvas.DrawShadow(center_x + i, j, s);
                        }
                    }
                }else if(center_x == xl){
                    for(int j = center_y; j > 0; j--){
                        for(int i = 0; i <= j; i++){
                            canvas.DrawShadow(center_x + radius + i, j, s);
                        }
                    }
                    for(int j = center_y; j > 0; j--){
                        for(int i = 0; i > j; i++){
                            canvas.DrawShadow(center_x - radius - i, j, s);
                        }
                    }

                }else{
                    for(int i = 0; i <= canvas.getW() - center_x; i++){
                        for(int j = 0; j < center_y; j++){
                            canvas.DrawShadow(center_x - i, center_y + radius - j, s);
                        }
                    }
                    for(int i = 0; i <= canvas.getW() - center_x; i++){
                        for(int j = 0; j < center_y; j++){
                            canvas.DrawShadow(center_x - i, j, s);
                        }
                    }
                }
            }else{
                if(center_x > xl){
                    for(int i = 0; i <= canvas.getW() - center_x; i++){
                        for(int j = 0; j < center_y; j++){
                            canvas.DrawShadow(center_x + i, center_y - radius + j + i, s);
                        }
                    }
                    for(int i = 0; i <= canvas.getW() - center_x; i++){
                        for(int j = 0; j < center_y; j++){
                            canvas.DrawShadow(center_x + i, center_y + radius - j - i, s);
                        }
                    }
                    for(int i = 0; i <= canvas.getW() - center_x; i++){
                        for(int j = center_y - radius; j < center_y + radius; j++){
                            canvas.DrawShadow(center_x + i, j, s);
                        }
                    }
                }else{
                    for(int i = 0; i <= canvas.getW() - center_x; i++){
                        for(int j = 0; j < center_y; j++){
                            canvas.DrawShadow(center_x - i, center_y - radius + j + i, s);
                        }
                    }
                    for(int i = 0; i <= canvas.getW() - center_x; i++){
                        for(int j = 0; j < center_y; j++){
                            canvas.DrawShadow(center_x - i, center_y + radius - j - i, s);
                        }
                    }
                    for(int i = 0; i <= canvas.getW() - center_x; i++){
                        for(int j = center_y - radius; j < center_y + radius; j++){
                            canvas.DrawShadow(center_x - i, j, s);
                        }
                    }
                }
            }
        }
};

class Light{

    private:
        int x;
        int y;
        char symbol;

    public:
        Light(int x0, int y0, char s){
            x = x0;
            y = y0;
            symbol = s;
        }
        ~Light(){}

        void Shadow(ASCIICanvas &canvas, std::vector<std::unique_ptr<Figure>> &fig){
            for(auto &f : fig){
                f->Shadow(canvas, x, y, symbol);
            }
            canvas.Draw(x, y, '*');
        }

};

void parse(const std::string &conf_file, std::string &output_file, ASCIICanvas &canvas, std::vector<std::unique_ptr<Figure>> &fig, std::unique_ptr<Light> &light) {
    std::ifstream file(conf_file);

    if(!file){
        std::cout << "Nie ma takiego pliku!" << std::endl;
        exit(0);
    }

    std::string line;
    char empty = ' ';
    while (std::getline(file, line)){
        std::stringstream str(line);
        std::string s;
        str >> s;

        if (s == "canvas"){
            int w, h;
            str >> w >> h;
            canvas = ASCIICanvas(w, h);
        }else if(s == "output") {
            str >> output_file;
        }else if(s == "empty_symbol"){
            str >> empty;
            for (int i = 0; i < canvas.getH(); i++) {
                for (int j = 0; j < canvas.getW(); j++) {
                    canvas.Draw(j, i, empty);
                }
            }
        }else if(s == "rectangle"){
            int x, y, w, h;
            char symbol;
            str >> x >> y >> w >> h >> symbol;
            fig.push_back(std::make_unique<Rectangle>(x, y, w, h));
            fig.back()->Draw(canvas, symbol);
        }else if(s == "square"){
            int x, y, w;
            char symbol;
            str >> x >> y >> w >> symbol;
            fig.push_back(std::make_unique<Square>(x, y, w));
            fig.back()->Draw(canvas, symbol);
        }else if(s == "circle"){
            int x, y, r;
            char symbol;
            str >> x >> y >> r >> symbol;
            fig.push_back(std::make_unique<Circle>(x, y, r));
            fig.back()->Draw(canvas, symbol);
        }else if(s == "light"){
            int x, y;
            char shadow;
            str >> x >> y >> shadow;
            light = std::make_unique<Light>(x, y, shadow);
        }
    }
}

auto main(int argc, char* argv[]) -> int{

    if(argc != 2){
        std::cout << "Niepoprawna liczba argumentow!" << std::endl;
        exit(0);
    }

    std::string conf_file = argv[1];
    std::string output_file;

    ASCIICanvas canvas(0,0);

    std::vector<std::unique_ptr<Figure>> fig;
    std::unique_ptr<Light> light;

    parse(conf_file, output_file, canvas, fig, light);

    if(light){
        light->Shadow(canvas, fig);
    }

    canvas.Save(output_file);

    return 0;
}