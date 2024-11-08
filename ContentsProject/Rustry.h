#pragma once

// Ό³Έν :
class Rustry
{
public:
	// constrcuter destructer
	Rustry();
	~Rustry();

	// delete Function
	Rustry(const Rustry& _Other) = delete;
	Rustry(Rustry&& _Other) noexcept = delete;
	Rustry& operator=(const Rustry& _Other) = delete;
	Rustry& operator=(Rustry&& _Other) noexcept = delete;

protected:

private:

};

