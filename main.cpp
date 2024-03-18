#include <SFML/Audio.hpp>

const int c_sampleRate = 44100;
const int c_center = 32767;

std::vector<sf::Int16> SquareWave(double _f, double _a, double _d) {
    std::vector<sf::Int16> out;
    int perhalf = c_sampleRate / (_f * 2);
    int rep = c_sampleRate * _d / perhalf;
    short a = c_center * _a;
    for (int i = 0; i < rep; i++)
    {
        for (int j = 0; j < perhalf; j++)
            out.push_back(a);
        for (int j = 0; j < perhalf; j++)
            out.push_back(-a);
    }
    return out;
}

std::vector<sf::Int16> addPause(std::vector<sf::Int16> wave, double _p)
{
    std::vector<sf::Int16> out = wave;
    int p = _p * wave.size();
    for (int i = 0; i < p; i++)
        out.push_back(short(0));
    return out;
}

int main()
{
    sf::SoundBuffer buffer;
	std::vector<sf::Int16> sample;
    double freq = 250;
    double amp = 1.0;
    double len = 0.2;
    double coeff = 0.5;
    double dur = 2.0;
    
    double rep = dur / len;
    std::vector<sf::Int16> beeptest = addPause(SquareWave(freq, amp, len * coeff), 1 - len * coeff);
    for (int i=rep; i>0; i--)
        sample.insert(sample.end(), beeptest.begin(), beeptest.end());

	buffer.loadFromSamples(&sample[0], sample.size(), 1, 44100);

	sf::Sound sound;
	sound.setBuffer(buffer);
	sound.play();
    sf::Time wait = sf::microseconds(int(dur * 1'000'000));
    sf::Clock c;
    sf::Time t = c.restart();
    while (t < wait) {t = c.getElapsedTime();}
    return 0;
}
