
//Simple integer based PID for the internal control loop
class internalPID {
  public:
    internalPID(float Kp, float Ki, float Kd) {
      this->Kp = Kp;
      this->Kd = Kd;
      this->Ki = Ki;
    }
    void clearIntegral() {
      error_integral = 0.0f;
    }
    void setSetpoint(int setpoint) {
      this->setpoint = setpoint;
    }
    void setSaturation(int min, int max) {
      min_out = min;
      max_out = max;
    }
    int update(int input) {
      current_time = micros();
      float del_t = (current_time - previous_time) / 1000000.0f;
      int error = setpoint - input;
      error_integral += float(error) * del_t;
      float del_error = (error - error_last) / del_t;
      int out = int(Kp * error + Ki * error_integral + Kd * del_error);
      error_last = error;
      previous_time = current_time;
      auto s = SIGN(out);
      out = CLAMP(abs(out), min_out, max_out);
      return s * out;
    }
  private:
    template <typename S> S CLAMP(const S value, const S low, const S high) {
      return value < low ? low : (value > high ? high : value);
    }
    template <typename S> S SIGN(S value) {
      return value < 0 ? static_cast<S>(-1) : static_cast<S>(1);
    }
    float Kp = 0.0f;
    float Kd = 0.0f;
    float Ki = 0.0f;
    int min_out = 0;
    int max_out = 0;
    int setpoint = 0;
    float output = 0;
    float error_integral = 0;
    float error_last = 0;
    unsigned long current_time = 0.0;
    unsigned long previous_time = 0.0;

};
