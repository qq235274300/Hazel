#pragma once


namespace Hazel
{
	class  Timestep
	{
	public:
		Timestep(float time = 0):m_Time(time)
		{

		}
		//means Timestep class Instance can cast float 
		operator float() {return m_Time;}

		float GetSeconds()const{return m_Time;}
		float GetMilliSeconds()const {return m_Time * 1000.f;}
	private:
		float m_Time;
	};
	
}