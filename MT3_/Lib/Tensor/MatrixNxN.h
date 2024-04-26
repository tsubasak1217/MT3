#pragma once
struct Matrix2x2 final {
	float m[2][2];

	Matrix2x2() {
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				m[i][j] = 0.0f;
			}
		}
	}

	Matrix2x2(const Matrix2x2& init) {
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				m[i][j] = init.m[i][j];
			}
		}
	}

	Matrix2x2(
		float aa, float ab,
		float ba, float bb
	) {
		m[0][0] = aa; m[0][1] = ab;
		m[1][0] = ba; m[1][1] = bb;
	}
};

struct Matrix3x3 final {
	float m[3][3];

	Matrix3x3() {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				m[i][j] = 0.0f;
			}
		}
	}

	Matrix3x3(const Matrix3x3& init) {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				m[i][j] = init.m[i][j];
			}
		}
	}

	Matrix3x3(
		float aa, float ab, float ac,
		float ba, float bb, float bc,
		float ca, float cb, float cc
	) {
		m[0][0] = aa; m[0][1] = ab; m[0][2] = ac;
		m[1][0] = ba; m[1][1] = bb; m[1][2] = bc;
		m[2][0] = ca; m[2][1] = cb; m[2][2] = cc;
	}
};

struct Matrix4x4 final {
	float m[4][4];

	Matrix4x4() {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				m[i][j] = 0.0f;
			}
		}
	}

	Matrix4x4(const Matrix4x4& init) {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				m[i][j] = init.m[i][j];
			}
		}
	}

	Matrix4x4(
		float aa, float ab, float ac, float ad,
		float ba, float bb, float bc, float bd,
		float ca, float cb, float cc, float cd,
		float da, float db, float dc, float dd
	) {
		m[0][0] = aa; m[0][1] = ab; m[0][2] = ac; m[0][3] = ad;
		m[1][0] = ba; m[1][1] = bb; m[1][2] = bc; m[1][3] = bd;
		m[2][0] = ca; m[2][1] = cb; m[2][2] = cc; m[2][3] = cd;
		m[3][0] = da; m[3][1] = db; m[3][2] = dc; m[3][3] = dd;
	}


	void operator=(const Matrix4x4& mat) {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				m[i][j] = mat.m[i][j];
			}
		}
	}
};